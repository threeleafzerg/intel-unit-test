import os
import json

import tensorflow as tf

os.environ['TF_CONFIG'] = json.dumps({
      'cluster': {
                'worker': ['localhost:6000', 'localhost:6001']
                    },
                        'task': {'type': 'worker', 'index': 0}
})

tf.contrib.distribute.run_standard_tensorflow_server().join()
