#include <stdio.h>

int main() {
  int peak_detection(int peaks[3], float nums[10968]);

  printf("Hello world");
  int peaks[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // float peaks[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  FILE *input = fopen("Data/prototype_slow2.txt", "r");
  if (input == NULL) {
    printf("File can't be opened");
  }
  // int size = 10968;
  float nums[10968];
  int size;
  fscanf(input, "%d", &size);
  int i = 0;
  while (!feof(input)) {
    fscanf(input, "%f", &nums[i]);
    // printf("\n%f", nums[i]);
    i++;
  }
  fclose(input);
  peak_detection(peaks, nums);
  for (int i = 0; i < 50; i++) {
    printf("\n%d", peaks[i]);
  }
  FILE *fp = fopen("peak_results.txt", "w");
  if (fp) {
    for (int i = 0; i < 50; i++) {
      fprintf(fp, "%d,", peaks[i]);
    }
  }
  fclose(fp);
  return 0;
}

int peak_detection(int peaks[3], float nums[10968]) {
  // int nums[15] = {4, 5, 6, 7, 6, 5, 4, 2, 3, 4, 5, 6, 8, 6, 5};
  float threshold = 1.0;

  // int j = 0;
  // for (int i = 1; i < 10968-1; i++) { // 10968
  //   // printf("\n%f", nums[i]);
  //   if (nums[i] > nums[i-1] && nums[i] > nums[i+1] && nums[i] > threshold) {
  //     if (j < 22) {
  //       peaks[j] = i;
  //       j++;
  //     }
  //   }
  // }

  int j = 0;
  int right = 0;
  int wait = -1;
  int curr_peak = 0;
  for (int i = 1; i < 10968-1; i++) { // 10968
    // printf("\n%f", nums[i]);
    if (nums[i] != nums[i+1] && nums[i] != nums[i-1]) {
      right = i-1;
    }
    if (nums[i] > nums[right] && nums[i] > nums[i+1] && nums[i] > threshold) {
      if (j < 50) {
        if (wait == -1 || (wait != -1 && nums[i] >= nums[curr_peak])) {
          curr_peak = i;
        }
        // curr_peak = i;
        wait = 0;
        // peaks[j] = i;
        // j++;
      }
    }
    if (wait != -1) {
      wait++;
    }
    if (wait == 150) {
      peaks[j] = curr_peak;
      j++;
      wait = -1;
    }
  }
  return 1;
}

// save indices to a file and use a dynamic allocated array
// dynamic allocate the peaks array as well
// error handling
// averaging box filter

// error analysis between peak of averaged signal vs peak of actual signal