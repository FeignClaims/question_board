************************************************************************************************************************
接口与实现相分离 (separate interface from implementation)
************************************************************************************************************************

当题目上要求接口与实现相分离, 一般来说分文件即可; 如果题目涉及类层次和继承则是在要求写一个抽象基类, 而其他具体类继承自它.

但实际进行分离远远不止这些, 想了解更多请阅读 `《Sixteen Ways to Stack a Cat》by Bjarne Stroustup`_.

========================================================================================================================
分文件
========================================================================================================================

:godbolt:`rsf76fMff`

.. literalinclude:: split/hello.hpp
  :language: cpp
  :linenos:
  :caption: hello.hpp

.. literalinclude:: split/hello.cpp
  :language: cpp
  :linenos:
  :caption: hello.cpp

.. literalinclude:: split/index.cpp
  :language: cpp
  :linenos:
  :caption: main.cpp

========================================================================================================================
抽象基类
========================================================================================================================

:godbolt:`GMcvPseeE`

.. literalinclude:: oo/base.hpp
  :language: cpp
  :linenos:
  :caption: base.hpp

.. literalinclude:: oo/concrete.hpp
  :language: cpp
  :linenos:
  :caption: concrete.hpp

.. literalinclude:: oo/concrete.cpp
  :language: cpp
  :linenos:
  :caption: concrete.cpp

.. literalinclude:: oo/index.cpp
  :language: cpp
  :linenos:
  :caption: main.cpp
