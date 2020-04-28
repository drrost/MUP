int *mx_sort_arr_int(int *arr, int size) {
  int temp;

  for (int j = 0; j < size-1; j++) {
    for (int i = 0; i < size - 1; i++) {
      if (arr[i] > arr[i+1]) {
	temp = arr[i];
	arr[i] = arr[i+1];
	arr[i+1] = temp;
      }
      else continue;
    }
  }
  return arr;
}
