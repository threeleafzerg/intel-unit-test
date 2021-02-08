import os
import json

import tensorflow as tf

os.environ['TF_CONFIG'] = json.dumps({
    'cluster': {
        'worker': ['127.0.0.1:6000', '127.0.0.1:6001']
    },
    'task': {'type': 'worker', 'index': 0}
})

tf.contrib.distribute.run_standard_tensorflow_server().join()
