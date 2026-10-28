#include "common.h"

void encoder_loop(void *pvParameters){
    for( ;; ){


    if((xQueueReceive(xPanCtrlInQueue, &panIn, portMAX_DELAY) == pdTRUE)
        && (xQueueReceive(xPanCtrlInQueue, &panIn, portMAX_DELAY) == pdTRUE)){
        uart1_print("\r\n<<<PID_CONTROLLER_VISION>>>\r\n");
        FSM_STATUS = CTRL;

        //updating reference
        panVisionRef = panIn;
        tiltVisionRef = tiltIn;

        uart1_print("\r\npanIn: 0x%04x, 0b%s, d:%d \r\n", panIn, rx_binary_string(panIn), panIn);
        uart1_print("tiltIn: 0x%04x, 0b%s, d:%d \r\n", tiltIn, rx_binary_string(tiltIn), tiltIn);
        //  taskYIELD();

    }

    if((xQueueReceive(xPanFbInQueue, &panEncMeasuredVal, portMAX_DELAY) == pdTRUE)
        && (xQueueReceive(xTiltFbInQueue, &tiltEncMeasuredVal, portMAX_DELAY) == pdTRUE)){



        //PAN CTRL OUT (to map then to motor) //TILT CTRL OUT (to map then to motor)
        if((xQueueSend(xPanCtrlOutQueue, &panOutput, 0) == pdTRUE)
        && (xQueueSend(xTiltCtrlOutQueue, &tiltOutput, 0) == pdTRUE)){
            uart1_print("\r\npanOutput:  0x%04x, 0b%s, d:%d \r\n", panOutput, rx_binary_string(panOutput), panOutput);
            uart1_print("tiltOutput:  0x%04x, 0b%s, d:%d \r\n", tiltOutput, rx_binary_string(tiltOutput), tiltOutput);
            taskYIELD();
        }else{

        taskYIELD();
        }
        }
    vTaskDelay(pdMS_TO_TICKS(1));
    }
}