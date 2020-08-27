// you can also use imports, for example:
import java.util.*;

// you can write to stdout for debugging purposes, e.g.
// System.out.println("this is a debug message");

class Solution {

    static char five = '5';

    public int solution(int N) {
        // write your code in Java SE 8
        // Can't call a method on a primite type so used Integer class
        String number = Integer.toString(N);

        if(number >= 0){
          number = positiveCase(number);
        }
        else{
          number = negativeCase(number);
        }
        return Integer.parseInt(number);

    }

    private String positiveCase(String digits){

      for(int i = 0; i < digits.length(); i++){
        if(five > digits.charAt(i)){

            return digits.substring(0, i) + five + digits.substring(i);
        }
      }
      return digits + five;
    }

    private String negativeCase(String digits){

      for(int i = 1; i < digits.length(); i++){
        if(five < digits.charAt(i)){

            return digits.substring(0, i) + five + digits.substring(i);
        }
      }
      return digits + five;
    }
}


/*
By far the most difficult task and rushed!

The task specified insering a '5' so declared a static char within the class that
could be used throughout the methods.

There are two cases, positive and negative.
- the positive case works by comparing 5 to the first index of the number and if
5 is greater than that number, it is added there. For example,
    - 432
    5 is greater than 4, and would make the maximum possible value by adding a 5
    by placing it at the beginning.
    - 670
    If we added 5 to the beginning, we would get 5670 but if we were to add 5 after
    the '7', we would get 6750 which is larger. Hence checking if the number at index
    0 then 1 then 2 etc is larger or smaller. This works the same for negative numbers
    but simply in reverse.

    Once we figure out where to add in the five, simple concatenate the string back
    together and return that.

    Back up in solution, we check if the number we are changing is positive or negative,
    then call the appropriate function on the number (String).

    At the very end, we change the string back to an int which we return.
}






*/
