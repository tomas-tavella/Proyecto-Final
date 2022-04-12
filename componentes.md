# Eleccion de componentes para el circuito

- Diodos: MUR1640CT x2 (400V de Vrmax y 8A de Imax) -- Disponible en Elemon
- Llaves: MOSFET IRFP150 x4 (100V de Vdsmax, 30A de Idmax y Rds(on) de 55mohm) -- Disponible en Elemon y SyC
- Drivers:
- Isolator: Tiene que llevar una senal por bus I2C, por lo que necesita aislar el CLK y los datos. Puede ser un par de ISO774x, o tal vez la serie ISO164x de aisladores para I2C es mejor (preguntar)
- Sensor I/V/P: Texas Instuments LM5056A -- 3 to 80V, 12-bit, I2C output
- DSP/MCU: Plaqueta Texas Instruments TMDSCNCD28335 -- TMS320F28335 DSP
