#include "I2c_slave_interrupt.h"
   

   TI2C_PARM  I2C_PARM;
   u8 MessageBegin;
   u8 tx_dt;
// ********************** Data link function ****************************
// * These functions must be modified according to your application neeeds *
// * See AN document for more precision
// **********************************************************************

	void I2C_transaction_begin(void)
	{
	  MessageBegin = TRUE;
	}
        
	void I2C_transaction_end(void)
	{
          I2C_PARM.RxLoc = 0;
          I2C_PARM.TxLoc = 0;
          MessageBegin = FALSE;
	}
        
	void I2C_byte_received(u8 u8_RxData)
	{
           if(MessageBegin == TRUE)
           {
            I2C_PARM.RxBuf[I2C_PARM.RxLoc] = u8_RxData;
            I2C_PARM.RxLoc++;
           }
	}
                       
	u8 I2C_byte_write(void)
	{
        #if ADDR_LEN_16 
           I2C_PARM.TxLoc += I2C_PARM.RxBuf[0] + (I2C_PARM.RxBuf[1]<<8);
        #else
           I2C_PARM.TxLoc += I2C_PARM.RxBuf[0];
        #endif
           //tx_dt = I2C_PARM.RxBuf[I2C_PARM.TxLoc+1]; //������
           tx_dt = I2C_PARM.TxBuf[I2C_PARM.TxLoc];
           I2C_PARM.TxLoc++;
           return tx_dt;
	}

// ********************** Data link interrupt handler *******************

#if 0
        
#ifdef _RAISONANCE_
void I2C_Slave_check_event(void) interrupt 19 {
#endif
#ifdef _COSMIC_
@far @interrupt void I2C_Slave_check_event(void) {
#endif
	static u8 sr1;					
	static u8 sr2;
	static u8 sr3;
	
// save the I2C registers configuration
sr1 = I2C->SR1;
sr2 = I2C->SR2;
sr3 = I2C->SR3;

/* Communication error? */
  if (sr2 & (I2C_SR2_WUFH | I2C_SR2_OVR |I2C_SR2_ARLO |I2C_SR2_BERR))
  {		
    I2C->CR2|= I2C_CR2_STOP;  // stop communication - release the lines
    I2C->SR2= 0;					    // clear all error flags
	}
/* More bytes received ? */
  if ((sr1 & (I2C_SR1_RXNE | I2C_SR1_BTF)) == (I2C_SR1_RXNE | I2C_SR1_BTF))
  {
    I2C_byte_received(I2C->DR);
  }
/* Byte received ? */
  if (sr1 & I2C_SR1_RXNE)
  {
    I2C_byte_received(I2C->DR);
  }
/* NAK? (=end of slave transmit comm) */
  if (sr2 & I2C_SR2_AF)
  {	
    I2C->SR2 &= ~I2C_SR2_AF;	  // clear AF
		I2C_transaction_end();
	}
/* Stop bit from Master  (= end of slave receive comm) */
  if (sr1 & I2C_SR1_STOPF) 
  {
    I2C->CR2 |= I2C_CR2_ACK;	  // CR2 write to clear STOPF
		I2C_transaction_end();
  }
/* Slave address matched (= Start Comm) */
  if (sr1 & I2C_SR1_ADDR)
  {	 
		I2C_transaction_begin();
  }
/* More bytes to transmit ? */
  if ((sr1 & (I2C_SR1_TXE | I2C_SR1_BTF)) == (I2C_SR1_TXE | I2C_SR1_BTF))
  {
		I2C->DR = I2C_byte_write();
  }
/* Byte to transmit ? */
  if (sr1 & I2C_SR1_TXE)
  {
		I2C->DR = I2C_byte_write();
  }	
	GPIOD->ODR^=1;
}

#else

void I2C_Slave_check_event(void){

	static u8 sr1;					
	static u8 sr2;
	static u8 sr3;
	
// save the I2C registers configuration
        sr1 = I2C->SR1;
        sr2 = I2C->SR2;
        sr3 = I2C->SR3;

/* Communication error? */
  if (sr2 & (I2C_SR2_WUFH | I2C_SR2_OVR |I2C_SR2_ARLO |I2C_SR2_BERR))
  {		
    I2C->CR2|= I2C_CR2_STOP;  // stop communication - release the lines
    I2C->SR2= 0;	      // clear all error flags
   }
/* More bytes received ? */
  if ((sr1 & (I2C_SR1_RXNE | I2C_SR1_BTF)) == (I2C_SR1_RXNE | I2C_SR1_BTF))
  {
    I2C_byte_received(I2C->DR);
  }
/* Byte received ? */
  if (sr1 & I2C_SR1_RXNE)
  {
    I2C_byte_received(I2C->DR);
  }
/* NAK? (=end of slave transmit comm) */
  if (sr2 & I2C_SR2_AF)
  {	
    I2C->SR2 &= ~I2C_SR2_AF;	  // clear AF
		I2C_transaction_end();
	}
/* Stop bit from Master  (= end of slave receive comm) */
  if (sr1 & I2C_SR1_STOPF) 
  {
    I2C->CR2 |= I2C_CR2_ACK;	  // CR2 write to clear STOPF
		I2C_transaction_end();
	}
/* Slave address matched (= Start Comm) */
  if (sr1 & I2C_SR1_ADDR)
  {	 
		I2C_transaction_begin();
  }
/* More bytes to transmit ? */
  if ((sr1 & (I2C_SR1_TXE | I2C_SR1_BTF)) == (I2C_SR1_TXE | I2C_SR1_BTF))
  {
		I2C->DR = I2C_byte_write();
  }
/* Byte to transmit ? */
  if (sr1 & I2C_SR1_TXE)
  {
		I2C->DR = I2C_byte_write();
  }	
	GPIOD->ODR^=1;
}

#endif


// ************************* I2C init Function  *************************

void Init_I2C (void)
{
  u8 i;
  #ifdef I2C_slave_7Bits_Address
	  /* Set I2C registers for 7Bits Address */
                I2C->CR1 |= 0x01;				// Enable I2C peripheral
                I2C->CR2 = 0x04;			        // Enable I2C acknowledgement
		I2C->FREQR = 16; 			        // Set I2C Freq value (16MHz)
		I2C->OARL = (SLAVE_ADDRESS) ;	                // set slave address to 0x51 (put 0xA2 for the register dues to7bit address) 
		I2C->OARH = 0x40;		                // Set 7bit address mode
	#endif
                
	#ifdef I2C_slave_10Bits_Address
          /* Set I2C registers for 10Bits Address */
	  I2C->CR1 |= 0x01;				        // Enable I2C peripheral
	  I2C->CR2 = 0x04;					// Enable I2C acknowledgement
	  I2C->FREQR = 16; 					// Set I2C Freq value (16MHz)
	  I2C->OARL = (SLAVE_ADDRESS & 0xFF) ;		        // set slave address LSB 
	  I2C->OARH = 0xC0 | ((SLAVE_ADDRESS & 0x300) >> 7);	// Set 10bits address mode and address MSB
	#endif
	
	I2C->ITR	= 0x07;					// all I2C interrupt enable  
        
        I2C_PARM.RxLoc = 0;
        I2C_PARM.TxLoc = 0;
        MessageBegin = FALSE;
     
     for(i = 0; i < MAX_BUFFER; i++)
     {
        I2C_PARM.RxBuf[i] = 0;
        I2C_PARM.TxBuf[i] = 0x0;
     }
}




