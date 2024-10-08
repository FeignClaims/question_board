.. _storage_duration:

########################################################################################################################
存储周期 (storage duration): 带输出的构造、析构如何阅读?
########################################################################################################################

.. warning::

  对象的存储周期和存储周期是不同的概念, 但考试中并没有进行多少区分, 故此处也混合简化了两种概念.

  由于不清楚考试如何给的答案, 练习题中没有涉及一些模糊的和强制禁止优化也会被优化掉的地方 (例如用函数返回值构造具名对象).

.. toctree::
  :maxdepth: 1
  :caption: 目录

  preface.rst
  automatic_storage_duration.rst
  static_storage_duration.rst
  dynamic_storage_duration.rst
  thread_local_storage_duration.rst
  temporaries.rst
  mix.rst