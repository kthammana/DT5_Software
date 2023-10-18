#include <stdio.h>

int main() {
  int peak_detection(int peaks[3]);

  printf("Hello world");
  int peaks[] = {0, 0, 0};
  peak_detection(peaks);
  for (int i = 0; i < 3; i++) {
    printf("\n%d", peaks[i]);
  }
  FILE *fp = fopen("peak_results.txt", "w");
  if (fp) {
    for (int i = 0; i < 3; i++) {
      fprintf(fp, "%d,", peaks[i]);
    }
  }
  return 0;
}

int peak_detection(int peaks[3]) {
  int nums[15] = {4, 5, 6, 7, 6, 5, 4, 2, 3, 4, 5, 6, 8, 6, 5};
  int threshold = 7;

  int j = 0;
  for (int i = 1; i < 14; i++) {
    if (nums[i] > nums[i-1] && nums[i] > nums[i+1] && nums[i] > threshold) {
      peaks[j] = nums[i];
      j++;
    }
  }
  return 1;
}

// save indices to a file and use a dynamic allocated array
// plot indices on a graph with the original signal on python to visualize peaks