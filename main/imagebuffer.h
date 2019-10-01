
#ifndef IMAGEBUFFER_HEADER_1234
#define IMAGEBUFFER_HEADER_1234

class ImageBuffer {
  private:
  static const int BufferSize = 1024;
  
  uint8_t m_Data[BufferSize];
  int  m_ReadIndex;
  int  m_WriteIndex;

  uint8_t buffer_read() {
    if(m_WriteIndex > m_ReadIndex) { return m_Data[m_ReadIndex];}
    else{ return 0; }
  }
  
  uint8_t buffer_write(uint8_t value) {
    if(BufferSize > m_WriteIndex) { return m_Data[m_WriteIndex] = value; }
    else{ return 0; }
  }
  
  public:
  
  void ClearBuffer(){
    memset(m_Data, 0x0, BufferSize);
    m_ReadIndex = 0;
    m_WriteIndex = 0;
  }
  
  uint8_t* GetBufferHeadPtr(){ return m_Data; }
  
  int GetRemainedDataByte() { return m_WriteIndex - m_ReadIndex; }

  uint32_t Read_Byte(int numByte){
    if(numByte <= 0 || numByte > 4) {
      return 0;
    }
    
    uint32_t result = 0;
    for(int i=0 ; i<numByte ; ++i) {
      result += ((buffer_read() << (i * 8)));
    }
    
    return result;
  }

  void WriteByte(uint8_t value) {
    buffer_write(value);
  }
  
  ImageBuffer(){
    ClearBuffer();
  }
  
};


#endif
