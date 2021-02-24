int main(){
  DDRB = 0xff;
  while(true){
    PINB = 0xff;
    for(long i = 0; i<500000; ++i){
      asm("");
    }
  }
}
