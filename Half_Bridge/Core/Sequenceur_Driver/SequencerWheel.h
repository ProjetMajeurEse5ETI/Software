/*
 * Seq_Half_Bridge.h
 *
 *  Created on: Sep 26, 2024
 *      Author: augustin.laprais
 */

#ifndef SEQUENCEUR_DRIVER_SEQUENCERWHEEL_H_
#define SEQUENCEUR_DRIVER_SEQUENCERWHEEL_H_

#include "stm32f3xx_hal.h"
#include "main.h"


void testFunction(int del);
/**
  * @brief  Clear the ouput to control the H bridge for the BLDC.
  * @param  None
  * @retval None
  */
void resetOutput_R1(void);
/**
  * @brief  Clear the ouput to control the H bridge for the BLDC.
  * @param  None
  * @retval None
  */
void resetOutput_R2(void);

/**
  * @brief  Stop the BLDC.
  * @param  None
  * @retval oldHallSensor put in IDLE state
  */
void stopAlert(void);

/**
  * @brief  To run in horaire sense the selected BLDC following the pahse order.
  * If the order is not followed, the BLDC is stop.
  * @param  oldHallSensor is the old value of the Hall Sensor from the n-1 interruption.
  * @retval oldHallSensor with the new value of the Hall Sensor.
  */
void verityTableHoraire_R1(int8_t hallSensor);

/**
  * @brief  To run in anti-horaire sense the selected BLDC following the pahse order.
  * If the order is not followed, the BLDC is stop.
  * @param  oldHallSensor is the old value of the Hall Sensor from the n-1 interruption.
  * @retval oldHallSensor with the new value of the Hall Sensor.
  */
void verityTableHoraireAntiHoraire_R1(int8_t hallSensor);

/**
  * @brief  To run in horaire sense the selected BLDC following the pahse order.
  * If the order is not followed, the BLDC is stop.
  * @param  oldHallSensor is the old value of the Hall Sensor from the n-1 interruption.
  * @retval oldHallSensor with the new value of the Hall Sensor.
  */
void verityTableHoraire_R2(int8_t hallSensor);

/**
  * @brief  To run in anti-horaire sense the selected BLDC following the pahse order.
  * If the order is not followed, the BLDC is stop.
  * @param  oldHallSensor is the old value of the Hall Sensor from the n-1 interruption.
  * @retval oldHallSensor with the new value of the Hall Sensor.
  */
void verityTableHoraireAntiHoraire_R2(int8_t hallSensor);




#endif /* SEQUENCEUR_DRIVER_SEQUENCERWHEEL_H_ */
