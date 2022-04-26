
// #include "dif/dif_uart.h"
// #include "runtime/log.h"
// #include "runtime/print.h"
// #include "testing/check.h"
// 
// #include "testing/test_main.h"
// 
// #include "top_athos_sw/sw/autogen/top_athos.h" 

#include "dif/dif_uart.h"
#include "dif/log.h"
#include "dif/print.h"
#include "dif/check.h"
#include "dif/test_main.h"

#include "top_athos_sw/sw/autogen/top_athos.h" 

const test_config_t kTestConfig;
static dif_uart_t uart;

// perform the bubble sort
void bubbleSort(int array[], int size) {

  // loop to access each array element
  for (int step = 0; step < size - 1; ++step) {
    
    // check if swapping occurs  
    int swapped = 0;
    
    // loop to compare array elements
    for (int i = 0; i < size - step - 1; ++i) {
      
      // compare two array elements
      // change > to < to sort in descending order
      if (array[i] > array[i + 1]) {
        
        // swapping occurs if elements
        // are not in the intended order
        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
        
        swapped = 1;
      }
    }
    
    // no swapping means the array is already sorted
    // so no need for further comparison
    if (swapped == 0) {
      break;
    }
    
  }
}

// print array
void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    LOG_INFO("%d  ", array[i]);
  }
}

bool test_main(void) {

  // initialize uart
  CHECK(
      dif_uart_init(
          (dif_uart_params_t){
              .base_addr = mmio_region_from_addr(TOP_ATHOS_UART0_BASE_ADDR),
          },
          &uart) == kDifUartOk);
  CHECK(dif_uart_configure(&uart, (dif_uart_config_t){
                                      .baudrate = kUartBaudrate,
                                      .clk_freq_hz = kClockFreqPeripheralHz,
                                      .parity_enable = kDifUartToggleDisabled,
                                      .parity = kDifUartParityEven,
                                  }) == kDifUartConfigOk);
  base_uart_stdout(&uart);


  int data[] = {-2, 45, 0, 11, -9, 2, 99};

  // find the array's length
  int size = sizeof(data) / sizeof(data[0]);

  LOG_INFO("Original Array:");
  printArray(data, size);

  bubbleSort(data, size);

  LOG_INFO("Sorted Array:");
  printArray(data, size);
  return true;
}
