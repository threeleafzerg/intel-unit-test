import tensorflow as tf
from tensorflow.data import Dataset as tfd
from tensorflow.contrib.distribute import CollectiveAllReduceStrategy
from tensorflow.contrib.distribute import DistributeConfig


def input_fn():
    features = tfd.from_tensors([[1.]]).repeat(32)
    labels = tfd.from_tensors(1).repeat(32)
    return tfd.zip((features, labels))

def model_fn(features, labels, mode):
    layer = tf.layers.Dense(1)
    logits = layer(features)

    if mode == tf.estimator.ModeKeys.PREDICT:
        predictions = {"logits": logits}
        return tf.estimator.EstimatorSpec(mode, predictions=predictions)
    
    loss = tf.losses.mean_squared_error(
        labels=labels, predictions=tf.reshape(logits, []))

    if mode == tf.estimator.ModeKeys.EVAL:
        return tf.estimator.EstimatorSpec(mode, loss=loss)

    if mode == tf.estimator.ModeKeys.TRAIN:
        train_op = tf.train.GradientDescentOptimizer(0.2).minimize(loss)
        return tf.estimator.EstimatorSpec(mode, loss=loss, train_op=train_op)

train_spec = tf.estimator.TrainSpec(input_fn=input_fn)
eval_spec = tf.estimator.EvalSpec(input_fn=input_fn)

distribution = CollectiveAllReduceStrategy(num_gpus_per_worker=0)

config = tf.estimator.RunConfig(
    experimental_distribute=DistributeConfig(
        train_distribute=distribution,
        eval_distribute=distribution,
        remote_cluster={
            'worker': ['127.0.0.1:6000', '127.0.0.1:6001'],
        },
    )
)

estimator = tf.estimator.Estimator(model_fn=model_fn, config=config)
tf.estimator.train_and_evaluate(estimator=estimator,
                                train_spec=train_spec,
                                eval_spec=eval_spec)
