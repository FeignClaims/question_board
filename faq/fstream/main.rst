************************************************************************************************************************
文件读写
************************************************************************************************************************

通过 :cpp:`#include <fstream>` 中的 :cpp:`ofstream`、:cpp:`ifstream` 和 :cpp:`fstream` 文件流, 你可以对文件进行写入、读取或读写.

它们的用法于 :cpp:`cout` 和 :cpp:`cin` 相似, 因此请参考 :doc:`/faq/input_methods/main` 等了解. 以下解释如何打开文件、读取到了文件末尾和关闭文件.

========================================================================================================================
打开文件
========================================================================================================================

要使用文件流, 我们需要用它先打开一个文件:

.. code-block:: cpp
  :linenos:

  #include <fstream>
  using namespace std;

  int main() {
    ifstream ifile;
    ifile.open("C:/test.txt", std::ios_base::in);

    // 然后就能像 cin 一样使用 ifstream
    int value = 0;
    ifile >> value;
  }

这样就打开了一个文件, **但是何必呢?!**

你没必要指明 :cpp:`std::ios_base::in`, :cpp:`ifstream` (input file stream) 始终会给文件打开方式加上它:

.. code-block:: cpp
  :linenos:

  int main() {
    ifstream ifile;
    ifile.open("C:/test.txt");
  }

你没必要分出一行写, 可以在声明 :cpp:`ifile` 时就让它打开文件:

.. code-block:: cpp
  :linenos:

  int main() {
    ifstream ifile("C:/test.txt");
  }

"可是我之前的写法也是可以的啊……"
  1. 你如果不是为了读取文件的内容, 何必用 :cpp:`ifstream`? 既然用 :cpp:`ifstream` 就是想读取文件内容, 那何必再加一句 :cpp:`std::ios_base::in`? **你用 ifstream, 就是为了读取文件.**
  2. 你如果不是为了现在打开这个文件, 何必去声明 :cpp:`ifstream ifile`? 既然你声明 :cpp:`ifstream ifile` 就是要打开文件, 何必再在额外一行去写一个 :cpp:`ifile.open` 来打开文件? **你声明 ifstream ifile, 就是为了在此时此刻打开文件.**

  写代码必须注意代码的目的性, 没有明确代码各部分的目的是写不出代码的直接原因之一.

同理, :cpp:`ofstream` 会始终在打开方式中加上 :cpp:`std::ios_base::out`, :cpp:`fstream` 会始终在打开方式中加上 :cpp:`std::ios_base::in | std::ios_base::out`, **哪怕你给它其他的打开方式**.

========================================================================================================================
判断打开成功
========================================================================================================================

通过 :cpp:`ifile.is_open()`, 我们可以判断上一次打开文件是否成功:

.. code-block:: cpp
  :linenos:

  #include <cstdlib>  // for exit, EXIT_FAILURE, EXIT_SUCCESS

  int main() {
    ifstream ifile("C:/test.txt");
    if (!ifile.is_open()) {
      cerr << "错误信息\n";  // err 的意思是 error
      exit(EXIT_FAILURE);
    }
  }

========================================================================================================================
读取文件到末尾
========================================================================================================================

在课上可能像下面这样写, **千万千万千万千万** 不要用!!!

.. code-block:: cpp
  :linenos:

  int main() {
    ifstream ifile("C:/test.txt");
    for (int value = 0; !ifile.eof();) {  // 或者有些奇怪的老师会写 ifile.eof() == 0
      ifile >> value;

      cout << value;
    }
  }

是, 没错, 这样是可以判断文件到没到文件尾 (eof, end of file), 但是其他问题呢? 例如, 现在循环里是在读取 :cpp:`int` 类型, 那如果文件里有一个不是数字的字符呢? **读取将会失败, 你将永远不能达到文件尾, 这个循环将会永远继续下去**.

.. admonition:: 前置内容
  :class: precontent

  在往下看正确的方案之前, 请先阅读 :doc:`/faq/input_methods/main` 直到读完 "共同部分".

数据读写有三类错误状态: eof (到达读取数据的尾部)、fail (读写操作失败)、bad (读写流本身出现不可逆转的问题). **读写操作失败 fail** 才是你真正想要的, 它涵盖了 bad 和 eof 的几乎所有情况, 唯一没涵盖的某种 eof 情况也不是你真正想要的.

因此, 我们应该使用 :cpp:`!ifile.fail()` 来表达读取有没有结束, 而 :doc:`/faq/input_methods/main` 的共同部分已经说了怎么写:

.. code-block:: cpp
  :linenos:

  int main() {
    ifstream ifile("C:/test.txt");
    if (!ifile.is_open()) {  
      cerr << "打开文件失败!\n";
      exit(EXIT_FAILURE);
    }


    for (int value = 0; ifile >> value;) {
      cout << value;
    }

    if (ifile.bad()) {
      cerr << "读写流本身出现不可逆转的问题!\n";
      exit(EXIT_FAILURE);
    } else if (ifile.eof()) {
      cout << "成功读取到了文件尾!\n";
    } else if (ifile.fail()) {
      cerr << "读写操作出现问题!\n";
      exit(EXIT_FAILURE);
    }
  }

.. note::

  注意, :cpp:`ifile.good() != !ifile.fail()`, 就像下面表里列的那样, **但别去记这玩意**. 上面已经说了, 用 :cpp:`!ifile.fail()`!

  .. figure:: iostate.png

========================================================================================================================
关闭文件
========================================================================================================================

太长别看: 你不需要手动用 :cpp:`file.close()` 来关闭文件, 用这种方式只会让人知道你真的不会 C++.

C++ 中的对象存在 :doc:`生命期和存储周期 </faq/lifetime/index>` 的概念. 简单来说, 你在大括号 :cpp:`{}` 内声明的变量, 到 :cpp:`}` 时就会死掉.

.. code-block:: cpp
  :linenos:

  int main() {
    int value1 = 0;
    cin >> value1;

    if (value != 0) {
      int value2 = value1 * value1;
      cout << value2;
    }  // value2 死掉了

    cout << value2;  // 错误: value2 死都死了, 你不可能用它
  }  // value1 死掉了

当 :cpp:`ofstream`、:cpp:`ifstream` 和 :cpp:`fstream` 死掉时, **它们会自动关闭文件**.

.. code-block:: cpp
  :linenos:

  int main() {
    std::ifstream ifile("C:/test.txt");

    int value = 0;
    ifile >> value;
  }  // ifile 死了, 它自动关闭文件!!!

.. seealso::

  文件需要我们预先获取、之后释放, 因而是一种 "资源". 在 :doc:`/faq/basic_concepts/resource` 中, 我解释了资源的所有权问题和 C++ 中资源的最佳管理方案——RAII, 这就是 :cpp:`ofstream`、:cpp:`ifstream` 和 :cpp:`fstream` 采用的方案.

========================================================================================================================
读写同一个文件
========================================================================================================================

- 我们打开一个文件对它进行写入时, 是先将数据写入到缓冲区, 再在合适时候 (比如) 一次性从缓冲区写入到文件.
- 我们打开一个文件对它进行读取时, 是先将文件读入到缓冲区, 再从缓冲区中读取数据.

这意味着, 如果我们先用 :cpp:`ofstream` 写入文件, 在 :cpp:`ofstream` 还没有关闭文件时, 就用 :cpp:`ifstream` 可读取同一文件, 那么可能读取的是原来文件中的数据.

.. code-block:: cpp
  :linesno:

  int main() {
    ofstream ofile("C:/test.txt");
    ofile << 682132891;

    ifstream ifile("C:/test.txt");
    int value = 0;
    ifile >> value;  // 682132891? 还是别的什么?
  }

"这总能用 file.close() 了吧?" 但你觉得下面的代码方便阅读吗?

.. code-block:: cpp
  :linesno:

  int main() {
    ofstream ofile("C:/test.txt");
    ofile << 682132891;
    ofile.close();
    ifstream ifile("C:/test.txt");
    int value = 0;
    ifile >> value;
  }

你可以人为添加 :cpp:`{}`; 或者往往更好地, 既然是写入和读取是在做不同的事情, 为什么不写成分别的函数?

.. tabs::

  .. tab:: 人为添加 :cpp:`{}`

    .. code-block:: cpp
      :linenos:

      int main() {
        {
          ofstream ofile("C:/test.txt");
          ofile << 682132891;
        }
        {
          ifstream ifile("C:/test.txt");
          int value = 0;
          ifile >> value;
        }
      }

  .. tab:: 分别的函数

    不知道 :cpp:`string` 是啥? :ref:`求求你看天鹅书吧😭 <cpp>`

    .. code-block:: cpp
      :linenos:

      #include <string>  // for string
      using namespace std;

      void write_file(string file) {
        ofstream ofile(file);
        ofile << 682132891;
      }

      void read_file(string file) {
        ifstream ifile(file);
        int value = 0;
        ifile >> value;
      }

      int main() {
        string file = "C:/test.txt";
        write_file(file);
        read_file(file);
      }

当然你可以用既能写入又能读取的 :cpp:`fstream`, 但我认为反而过于麻烦了:

.. code-block:: cpp
  :linenos:

  int main() {
    fstream file("C:/test.txt");
    file << 682132891;

    file.seekp(0);  // 你能看懂这个函数是回到文件开头吗?

    int value = 0;
    ifile >> value;
  }

========================================================================================================================
二进制文件读写
========================================================================================================================

二进制文件读写见于 :doc:`/faq/binary_io/main`.