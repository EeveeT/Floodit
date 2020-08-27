// you can also use imports, for example:
import java.util.*;

// you can write to stdout for debugging purposes, e.g.
// System.out.println("this is a debug message");

class Solution {
    public int solution(int[] A) {

      Arrays.parallelSort(A);
      for(int i = A.length - 1; i >= 0; i--){
        if(A[i] <= 0){
          break;
        }
        if(Arrays.binarySearch(A, -A[i]) >= 0){
          return A[i];
        }
      }
      return 0;
    }
}


/*
Binary search is the quickest way to sort through the array but it has to be
sorted in order first. parallelSort is quicker than sort for large arrays,
as you can sort though multiple threads in an array as opposed to continuously.
If the array is small parallelSort could make you slower though.

I then looped through A from largest to smallest to find the largest numbers first
and then go smaller only if there was no corresponding negative number.

The second if statement is used to find -A[i] and if none is found, we go back to
the top of the loop, find the next largest A[i] then search to see if there is
a correspinding -A[i] and so on until we have looped through all the positive
numbers in the array. If no correspinding A[i] is found we return 0.

*/
