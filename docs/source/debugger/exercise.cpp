void impl(int* array, int size, int index) {
  if (index == size) {
    return;
  }

  int current = array[index];

  int i = 0;
  for (i = index - 1; i >= 0 && array[i] > current; --i) {
    array[i + 1] = array[i];
  }
  array[i + 1] = current;

  impl(array, size, index + 1);
}

void function(int* array, int size) {
  impl(array, size, 0);
}
int main() {
  int array[] = {7, 6, 5, 4, 3, 2, 1};
  function(array, sizeof(array) / sizeof(array[0]));
}