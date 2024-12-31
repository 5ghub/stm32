#include <stdint.h>

String OBD_TYPE[]=
{
  "NO OBD SUPPORT",
  "OBD-II as defined by the CARB",
  "OBD as defined by the EPA",
  "OBD and OBD-II",
  "OBD-I",
  "Not OBD compliant",
  "EOBD (Europe)",
  "EOBD and OBD-II",
  "EOBD and OBD",
  "EOBD, OBD and OBD II",
  "JOBD (Japan)",
  "JOBD and OBD II",
  "JOBD and EOBD",
  "JOBD, EOBD, and OBD II",
  "Reserved",
  "Reserved",
  "Reserved",
  "Engine Manufacturer Diagnostics (EMD)",
  "Engine Manufacturer Diagnostics Enhanced (EMD+)",
  "Heavy Duty On-Board Diagnostics (Child/Partial) (HD OBD-C)",
  "Heavy Duty On-Board Diagnostics (HD OBD)",
  "World Wide Harmonized OBD (WWH OBD)",
  "Reserved",
  "Heavy Duty Euro OBD Stage I without NOx control (HD EOBD-I)",
  "Heavy Duty Euro OBD Stage I with NOx control (HD EOBD-I N)",
  "Heavy Duty Euro OBD Stage II without NOx control (HD EOBD-II)",
  "Heavy Duty Euro OBD Stage II with NOx control (HD EOBD-II N)",
  "Reserved",
  "Brazil OBD Phase 1 (OBDBr-1)",
  "Brazil OBD Phase 2 (OBDBr-2)",
  "Korean OBD (KOBD)",
  "India OBD I (IOBD I)",
  "India OBD II (IOBD II)",
  "Heavy Duty Euro OBD Stage VI (HD EOBD-IV)"
};

bool ReadPID(unsigned int Code, uint8_t *DataArray, float *Value1, float *Value2, float *Value3, float *Value4, float *Value5)
{
  *Value1 = *Value2 = *Value3 = *Value4 = *Value5 = -1;
  uint32_t ValInt32;
  
  //Calculate formula to get correct units
  switch(Code)
  { 
    case 0x01:                       
       *Value1 = DataArray[3];
       *Value2 = DataArray[4];
       *Value3 = DataArray[5];
       *Value4 = DataArray[6];
    break;

    case 0x03:
      *Value1 = DataArray[3];
      *Value2 = DataArray[4];    
    break;
        
    case 0x06:
    case 0x07:
    case 0x08:
    case 0x09:
       ValInt32 = DataArray[3];
       *Value1 = (100.0/128.0)*ValInt32 - 100;
    break;

    case 0x0A:
        ValInt32 = DataArray[3];  
       *Value1 = 3.0*ValInt32;
    break;
    
    case 0x0C:
       ValInt32= DataArray[3] << 8;
       ValInt32|= DataArray[4];   
       *Value1 = ValInt32/4;
    break;
    
    case 0x0E:
      ValInt32 = DataArray[3];    
      *Value1 = (ValInt32/2.0)-64.0;
    break;

    case 0x10:
       ValInt32= DataArray[3] << 8;   
       ValInt32|= DataArray[4];   
      *Value1 = ValInt32/100.0;
    break;

    case 0x14:
    case 0x15:
    case 0x16:    
    case 0x17:        
    case 0x18:
    case 0x19:    
    case 0x1A:        
    case 0x1B: 
       ValInt32 = DataArray[3];
       *Value1 = ValInt32/200;
       ValInt32 = DataArray[4];
       *Value2 = ValInt32/200;
    break;

    case 0x22:
      ValInt32 = DataArray[3];      
      *Value1 = 0.079*ValInt32;
    break;

    case 0x24:
    case 0x25:
    case 0x26:    
    case 0x27:        
    case 0x28:
    case 0x29:    
    case 0x2A:        
    case 0x2B:
      ValInt32  = DataArray[3] << 24;     
      ValInt32 |= DataArray[4];      
      *Value1 = ValInt32*2/65536;
      ValInt32  = DataArray[5] << 24;     
      ValInt32 |= DataArray[6];       
      *Value2 = ValInt32*8/65536;
    break;
        
    case 0x2D:
       ValInt32= DataArray[3];       
      *Value1 =  ((100.0/128.0)*ValInt32)-100.0;
    break;

    case 0x32:
      ValInt32  = DataArray[3] << 24;     
      ValInt32 |= DataArray[4]; 
      *Value1 =  ((~(uint32_t)ValInt32)+1)/4;
    break;

    case 0x34:
    case 0x35:
    case 0x36:    
    case 0x37:        
    case 0x38:
    case 0x39:    
    case 0x3A:        
    case 0x3B:
      ValInt32  = DataArray[3] << 24;     
      ValInt32 |= DataArray[4];  
      *Value1 = ValInt32*2/65536;
      ValInt32  = DataArray[5] << 24;     
      ValInt32 |= DataArray[6];         
      *Value2 = ValInt32/256;
      *Value2 -= 128;
    break;

    case 0x3C:
    case 0x3D:
    case 0x3E:    
    case 0x3F:
      ValInt32  = DataArray[3] << 24;     
      ValInt32 |= DataArray[4];  
      *Value1 = ValInt32/10;
      *Value1 -= 40; //this fixed a bug and I do not know why
    break;

    case 0x41:   
       *Value1 = DataArray[3];
       *Value2 = DataArray[4];
       *Value3 = DataArray[5];
       *Value4 = DataArray[6];
    break;
            
    case 0x42:
      ValInt32  = DataArray[3] << 24;     
      ValInt32 |= DataArray[4];  
      *Value1 = ValInt32/1000.0;
    break;

    case 0x43:
      ValInt32  = DataArray[3] << 24;     
      ValInt32 |= DataArray[4];   
      *Value1 = (100.0/255.0)*ValInt32;
    break;
    
    case 0x44:
      ValInt32  = DataArray[3] << 24;     
      ValInt32 |= DataArray[4];     
      *Value1 = (2.0/65536.0)*ValInt32;
    break;
   
    case 0x4F:
       *Value1 =  DataArray[3];
       *Value2 =  DataArray[4];
       *Value3 =  DataArray[5];
       *Value4 =  DataArray[6]*10;
    break;

    case 0x50:
       *Value1 =  DataArray[3]*10;
    break;

    case 0x53:
      ValInt32  = DataArray[3] << 24;     
      ValInt32 |= DataArray[4];    
      *Value1 = ValInt32/200;
    break;

    case 0x54:
      ValInt32  = DataArray[3] << 24;     
      ValInt32 |= DataArray[4];   
      *Value1 = (~((uint32_t)ValInt32))+1;
    break;

    case 0x55:
    case 0x56:
    case 0x57:    
    case 0x58:
       *Value1 = DataArray[3]*100/128;
       *Value1 -= 100;
       *Value2 = DataArray[4]*100/128;
       *Value2 -= 100;
    break;
                       
    case 0x5D:
      ValInt32  = DataArray[3] << 24;     
      ValInt32 |= DataArray[4];  
      *Value1 = (ValInt32/128.0)-210.0;
    break;
    
    case 0x5E:
      ValInt32  = DataArray[3] << 24;     
      ValInt32 |= DataArray[4];  
      *Value1 = ValInt32/20;
    break;

    case 0x61:
    case 0x62:
      ValInt32  = DataArray[3];     
      *Value1 = ValInt32-125;
    break;
    
    case 0x64:
       *Value1 = DataArray[3];
       *Value1 -= 125;

       *Value2 = DataArray[4];
       *Value2 -= 125;

       *Value3 = DataArray[5];
       *Value3 -= 125;
       
       *Value4 = DataArray[6];
       *Value4 -= 125;

       *Value5 = DataArray[7];     
       *Value5 -= 125;

    break;

    case 0x66:     
      *Value1 = DataArray[3] ;
      ValInt32  = DataArray[4] << 16;     
      ValInt32 |= DataArray[5];       
       *Value2 = ValInt32/32;
      ValInt32  = DataArray[6] << 16;     
      ValInt32 |= DataArray[7];          
       *Value3 = ValInt32/32;
    break;

    case 0x67:
    case 0x68: 
       *Value1 = DataArray[3];
       *Value2 = DataArray[4] -40;
       *Value3 = DataArray[5] -40;
    break;

    case 0x7C:
      ValInt32  = DataArray[3] << 16;     
      ValInt32 |= DataArray[4];   
      *Value1 = ValInt32/10;
      *Value1 -= 40;
    break;

    case 0x8E:
       ValInt32= DataArray[3] ;       
       *Value1 = ValInt32 -125;
    break;

    case 0xA2:
      ValInt32  = DataArray[3] << 16;     
      ValInt32 |= DataArray[4];  
      *Value1 = ValInt32/32;
    break;

    case 0xA4:
      ValInt32  = DataArray[5] << 16;     
      ValInt32 |= DataArray[6];  
      *Value2 = ValInt32/1000;
    break;

    case 0xA5: 
      *Value1 = DataArray[3];
      *Value2 = DataArray[4]/2;
    break;
    
    case 0xA6:
      ValInt32  = DataArray[3] << 24; 
      ValInt32 |= DataArray[4] << 16; 
      ValInt32 |= DataArray[5] << 8;     
      ValInt32 |= DataArray[6];  
      *Value1 = ValInt32/10;
    break;
        
    case 0x04:
    case 0x11:
    case 0x2C:
    case 0x2E:  
    case 0x2F:
    case 0x47:
    case 0x48:
    case 0x49:    
    case 0x4A:        
    case 0x4B:
    case 0x4C:   
    case 0x52:    
    case 0x5A:    
    case 0x5B:
       ValInt32 = DataArray[3];
      *Value1 =  (100.0/255.0)*ValInt32;
    break;

    case 0x23:
    case 0x59:
      ValInt32  = DataArray[3] << 16; 
      ValInt32 |= DataArray[4]; 
      *Value1 = 10.0*ValInt32;
    break;

    case 0x05:
    case 0x0F:
    case 0x46:
    case 0x5C:
       ValInt32= DataArray[3];
      *Value1 = ValInt32-40.0;
    break;

    case 0x69:    
      *Value1 = DataArray[3];
    break;
            
    case 0x20:    
    case 0x40:   
    case 0x60:    
      ValInt32  = DataArray[3] << 24; 
      ValInt32 |= DataArray[4] << 16; 
      ValInt32 |= DataArray[5] << 8; 
      ValInt32 |= DataArray[6]; 
      *Value1 = ValInt32;
    break;

    case 0x02:
    case 0x1F:    
    case 0x21:    
    case 0x31:      
    case 0x4D:
    case 0x4E:        
    case 0x63:
    case 0x65:           
      ValInt32  = DataArray[3] << 16; 
      ValInt32 |= DataArray[4]; 
      *Value1 = ValInt32;
    break;
    
    case 0x0B:
    case 0x0D:
    case 0x12:
    case 0x13:
    case 0x1C:
    case 0x1D:
    case 0x1E:    
    case 0x30:
    case 0x33:                 
    case 0x45:    
    case 0x51: 
    case 0x5F:       
       ValInt32= DataArray[3];   
      *Value1 = ValInt32;
    break;      

    case 0x6A:    
    case 0x6B:    
    case 0x6C:    
    case 0x6D:    
    case 0x6E:    
    case 0x6F:   
    case 0x70:   
    case 0x71:   
    case 0x72:   
    case 0x73:   
    case 0x74:   
    case 0x75:   
    case 0x76:   
    case 0x77:   
    case 0x78:   
    case 0x79:            
    case 0x7A:   
    case 0x7B:   
    case 0x7D:   
    case 0x80:   
    case 0x81:   
    case 0x82:   
    case 0x83:   
    case 0x84:   
    case 0x85:   
    case 0x86:   
    case 0x87:   
    case 0x88:   
    case 0x89:            
    case 0x8A:   
    case 0x8B:   
    case 0x8C:      
    case 0x8D:   
    case 0x8F:    
    case 0xA0:   
    case 0xA1:    
    case 0xA3:   
    case 0xA7:   
    case 0xA8:
    case 0xA9:            
    case 0xAA:   
    case 0xAB:   
    case 0xAC:      
    case 0xAD:   
    case 0xAE:   
    case 0xAF:  
      *Value1= (~0);
    break;
        
  }

   return true;
}
