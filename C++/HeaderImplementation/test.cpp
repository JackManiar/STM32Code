#include <cstdio>
#include <cstdint>

int main(){


for(uint8_t col = 1; col < 7; col++){
          for(uint8_t row = 1; row < 13; row++){
              if(row < 10)
                  printf("%d\n",100+(10*col)+row);
              else
                  printf("%d\n", (1000+(100*col)+row));
          }
      }

    }