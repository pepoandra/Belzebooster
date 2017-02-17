![Logo](/img/logo.png)


Digital guitar pedal with several effects written in **C** for the **DSPIC30F2012** micro-controller.

For this project, the team designed both the hardware and the software to build a **guitar pedal** with digital effects and **true by-pass**. 
  As shown below, the system consists of an antialiasing filter to ensure best sampling, an **A/D converter** which is integrated in the micro-controller, the **DSPIC3040** and an **D/A converter**.


![Pedal_Diagram](/img/guitar.png)


# Effects 

### Tremolo

  This effect is an amplitude modulation which can change the amplitude and period of the signal. It gives the signal an oscilating sound. In order to be a modulation of the signal and not an audible signal added to the original one, the frequency of the modulation has to be lower than 20 Hz, so the ranges of frequencies available for this modulation goes from 1.54 Hz  to 7.7Hz. The other parameter of this function is the minimum amplitude that the signal may reach. 

### Octavatron 
  This effect mirrors the negative part of the input signal onto the positive part. This makes the sound louder and of a higher frequency. When properly set up, it is possible to get a perfect octave up with respect to the input signal. 
 If the output signal's amplitude is greater than what the **D/A converter** can handle, then it is clipped by 
 ![Formula](/img/formula.png)
 
 
### Distorsion
   This effect clips peaks of the input signal to a certain cut-off value that is regulated by a potentiometer. Squaring the input signal adds several harmonic frequencies to the sound, making it brighter and more complete. This emulates the effect of a saturated amplifier. Moreover, the signal is then modulated by either a square, triangle or sinusoidal. The frequency of the modulation varies from 1 to 15Hz.
  
  
   ![Formula](/img/graphs.png)

  

