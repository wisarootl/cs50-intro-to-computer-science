# ML Research Framework

#### Video Demo: https://youtu.be/VZwic9ZzJqY

#### Description:

##### Background

- This is a software built with Python
- It is abstraction layers of multiple machine learning library including Sci-Kit learn, XGBoost, Imblearn, Tensorflow etc.

##### Design Pattern

- Design with Monad and Functional
- Consists of 2 entities: DataPod and Transformer

##### DataPod

- DataPod is a enriched dataframe
- Built on top of pandas dataframe
- Have special getter method to facilitate ML research
- e.g., `data_pod.entire_data`, `data_pod.train_X`, `data_pod.valid_Y`

##### Transformer

- Transformer is functions to transform DataPod
- Take DataPod in and return DataPod
- Many types of transformers
  - Splitter : split data into train, validation and test sets
  - CrossValidator : generate different train and validation set
  - Imputer: impute missing value
  - Encoder: encode feature to be more meaningful
  - Sampler: synthesize more record
  - Model: machine learning model to create prediction
  - Calibrator: calibrate prediction

##### Transformer and DataPod in action

- One transformer

```
data_pod = data_pod.fit_transform(transformer)
```

- Multiple Transformers

```
data_pod = data_pod.fit_transform(transformer1) \
                   .fit_transform(transformer2) \
                   .fit_transform(transformer3) \
                   .fit_transform(transformer4) \
                   .fit_transform(transformer5)
```

- Do some inspection between transformers

```
data_pod = data_pod.fit_transform(transformer1) \
                   .fit_transform(transformer2) \
                   .fit_transform(transformer3)

do_some_inspection(data_pod)

data_pod = data_pod.fit_transform(transformer4) \
                   .fit_transform(transformer5)
```

##### Branching

- Transformer wrapper

  - Higher-order function that take transformer in and return transformer out.
  - Serializer: connect transformer in series
  - Parallelizer: connect transformer in parallel

- Example branching

![Branching Example](/assets/branching-example.png)

```
pipeline_b = Parallelizer(transformers=[
                            transformer_b1,
                            transformer_b2,
                            transformer_b3
                            ]
                          )
```

```
pipeline_c = Parallelizer(transformers=[
                            transformer_c1,
                            transformer_c2,
                            transformer_c3
                            ]
                          )
```

```
pipeline_bc = Serializer(transformers=[
                            pipeline_b,
                            pipeline_c
                            ]
                          )
```

```
pipeline = Parallelizer(transformers=[
                            transformer_a,
                            pipeline_bc
                            ]
                          )

data_pod_list = data_pod.fit_transform(pipeline)
```
