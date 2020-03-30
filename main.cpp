//
//  main.cpp
//  stringtobyte
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];
  
  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;
      
      for (i = 0; (i < 4); i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }
  
  if (i)
  {
    for (j = i; j < 3; j++)
      char_array_3[j] = '\0';
    
    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    
    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];
    
    while ((i++ < 3))
      ret += '=';
    
  }
  
  return ret;
}

unsigned char* HexToBytes(const std::string& hex) {
  unsigned char* bytes = new unsigned char[15];
  
  int j = 0;
  
  for (unsigned int i = 0; i < hex.length(); i += 2) {
    std::string byteString = hex.substr(i, 2);
    unsigned char byte = (char)strtol(byteString.c_str(), NULL, 16);
    bytes[j++] = byte;
  }
  
  return bytes;
}

int main()
{
  std::string s = /*"ee60af52e51d3570bc36c3a6beb6584a"*/"e6c346bfcb0a3f62953ac8f95f73f369";
  unsigned char* v = HexToBytes(s);
  std::cout << *v << std::endl;
  
  std::cout << base64_encode(v, 16);
}

