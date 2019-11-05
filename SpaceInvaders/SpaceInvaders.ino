/*    Henry Gilbert
      Arudino Space Invaders
      Date: 11/2/2019

      Materials required:



      Project Inputs:



      Game Rules:




      Circuit limitations:




      Description:

*/

/* Global Variables: 


*/
// LED matrix definitions
const int R1 = 38 ;
const int R2 = 40 ;
const int R3 = 42 ;
const int R4 = 44 ;
const int R5 = 46 ;
const int R6 = 48 ;
const int R7 = 50 ;
const int R8 = 52 ;
const int C1 = 53 ;
const int C2 = 51 ;
const int C3 = 49 ;
const int C4 = 47 ;
const int C5 = 45 ;
const int C6 = 43 ;
const int C7 = 41 ;
const int C8 = 39 ;

// Create an array for the row and column pin outputs of
// the LED matrix.
int led_rows[8] = {R1, R2, R3, R4, R5, R6, R7, R8};
int led_cols[8] = {C1, C2, C3, C4, C5, C6, C7, C8};

void setup() {
  pinMode(R1, OUTPUT);  pinMode(C1, OUTPUT);
  pinMode(R2, OUTPUT);  pinMode(C2, OUTPUT);
  pinMode(R3, OUTPUT);  pinMode(C3, OUTPUT);
  pinMode(R4, OUTPUT);  pinMode(C4, OUTPUT);
  pinMode(R5, OUTPUT);  pinMode(C5, OUTPUT);
  pinMode(R6, OUTPUT);  pinMode(C6, OUTPUT);
  pinMode(R7, OUTPUT);  pinMode(C7, OUTPUT);
  pinMode(R8, OUTPUT);  pinMode(C8, OUTPUT);
  Serial.begin(9600);
  // Set default LED states.
  for (int i = 0; i < 8; i++) {
    digitalWrite(led_rows[i], LOW);
  }
}

int board[8][8] = {
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 1, 0, 1, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 1, 0, 0, 1, 0},
  {0, 1, 1, 0, 1, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 1},
  {1, 0, 1, 1, 0, 0, 0, 1},
};

/*    ===========================================================================
      Function: write_leds_from_matrix
      Parameters: (int) delay resolution : miliseconds desired for delay.
      Returns: None
      Description: Nested iteration through the 8x8 array for the matrix.
        If an ixj index reads 1, turn the corresponding LED on. This method
         will only light up one single LED at a time. Turns off after each
         iteration.

*/
void write_leds_from_matrix(int resolution)
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (board[i][j] == 1)
      {
        write_point(i, j);
        delay(resolution);
        clear_leds(resolution);
      }
    }
  }
}

/*  ===========================================================================
      Function: write_leds_from_matrix_reverse
      Parameters: (int) delay resolution : miliseconds desired for delay.
      Return: None
      Description: Nested iteration through the 8x8 array for the matrix.
        If an ixj index reads 1, turn the corresponding LED on. This method
        will only light up one single LED at a time. Turns off after each
        iteration. This function starts from the end at works backwards.
    ===========================================================================
*/

void write_leds_from_matrix_reverse(int resolution)
{
  for (int i = 8; i > 0; i--)
  {
    for (int j = 8; j > 0; j--)
    {
      if (board[i][j] == 1)
      {
        write_point(i, j);
        delay(resolution);
        clear_leds(resolution);
      }
    }
  }
}



// Clears all LEDs to allow for calculation reset
void clear_leds(int res) {
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(led_rows[i], LOW);
    digitalWrite(led_cols[i], HIGH);
  }
  delay(res);
}

/*    ===========================================================================
        Function: write_point
        Parameters: int r: row index for desired point to write. Starts at 0.
        Returns: None
        Description:
      ===========================================================================
*/
void write_point(int r, int c)
// Input the REAL matrix desired point, not the index.
{
  digitalWrite(led_rows[r], HIGH);
  for (int i = 0; i < 8; i++)
  {
    if ( i != c)
    {
      digitalWrite(led_cols[i], HIGH);
    }
    else
    {
      digitalWrite(led_cols[i], LOW);
    }
  }
}

/*  ===========================================================================
        Function: test_lights
        Parameters: None
        Return: None
        Description: Iterates through the LED matrix (NOT the array) and writes
    ===========================================================================
*/

void test_lights()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      write_point(i, j);
      delay(20);
      clear_leds(10);
    }
  }
  for (int i = 8; i >= 0; i--)
  {
    for (int j = 8; j >= 0; j--)
    {
      write_point(i, j);
      delay(20);
      clear_leds(10);
    }
  }


}


/*   ===========================================================================
        Function: write_block
        Parameters:  int row_a: start index (0-7) of the desired block to be written.
                     int row_b: end index (0-7) of the desired block to be written.
                     int col: desired column (0-7) to write the rows
        Returns: None
        Description: The written block will go from rows a-b all present on column col.
                     Uses two for loops. The first iterates between rows a-b and turns on
                     all the desired rows. The second loop starts at zero and turns off every
                     column except for the col parameter. Validated through "if(i!=col)".
     ===========================================================================
*/
void write_block(int row_a, int row_b, int col)
{
  for (int i = row_a; i <= row_b; i++)
  {
    digitalWrite(led_rows[i], HIGH);
  }

  for (int i = 0; i < 8; i++)
  {
    if (i != col)
    {
      digitalWrite(led_cols[i], HIGH);
    }
    else
    {
      digitalWrite(led_cols[i], LOW);
    }
  }
}


void loop() {
  for (int i = 2; i < 8; i++)
  {
    write_block(i, i + 2, 4);
    delay(20);
    clear_leds(50);



  }



}
