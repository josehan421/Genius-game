
void players(){                    //controlar se é single player ou multiplayer

   if(~chave){                     //se a chave estiver fechada, modo singleplayer

      modo = 0 ;                   //modo singleplayer
      
      for(i = 0; i<10; i++){       //pisca cinco vezes o led do jogador 1 indicando o sigleplayer
      
        jog1 = ~jog1;
        delay_ms(150);

      }
      
   }
   else{                          //se a chave estiver aberta, multiplayer
   
     modo = 1;                    //modo mutiplayer
     for(i = 0; i<10; i++){       //pisca cinco vezes os leds dos jogadores 1 e 2 indicando o multiplayer

          jog1 = ~jog1;
          jog2 = ~jog2;
          delay_ms(150);

      }
   
   }

}


//Essa função controla os leds indicadores de jogada, quando um jogador começa a jogar
//o estado do seu led é comutado, em setup todo o PORTD está em nível baixo, então o
//led acende, quando a função é execultada de novo, com fim da jogada, o led apaga
led_jogadores(){

     if(vez == 0){              //se o jogador 1 está jogando...
     
        jog1 = ~jog1;           //comuta o led indicador de jogada do jogador 2
     
     }
     
     if(vez == 1){              //se o jogador 2 está jogando...
     
        jog2 = ~jog2;           //comuta o led indicador de jogada do jogador 2
     
     }

}

void setup(){                      //configura PIC

// ======comparadores=======
   ADCON1 = 0x0F;                  //todos os pinos como digitais

// =========Timer 0==========
   T0CON = 0b11000010;            //Timer 0 ativo, 8 bits, clock interno, PRE 1:8


   TMR0L = 0;                     //estoro Timer 0 -> TMR0 * ciclo de maquina * prescale
                                  //                  (256 - 6) * 0,2us * 8 = 400us ou 0,4ms

// =========Portas==========
   TRISD = 0x00;                  //PORTD como saída
   PORTD = 0x00;                  //inicia todo PORTD em 0 (importante!)
   RBPU_bit = 0;                  //resistores de pull-up PORTB ativados
   TRISB = 0xFF;                  //PORTB como entrada
}


void output1(){

     led1 = 1;                   //liga led vermelho
     delay_ms(300);              //espera um tempo
     led1 = 0;                   //desliga led vermelho
     delay_ms(300);              //espera um tempo
}

void output2(){

     led2 = 1;                   //liga led amarelo
     delay_ms(300);              //espera um tempo
     led2 = 0;                   //desliga led amarelo
     delay_ms(300);              //espera um tempo
}

void output3(){

     led3 = 1;                   //liga led verde
     delay_ms(300);              //espera um tempo
     led3 = 0;                   //desliga led verde
     delay_ms(300);              //espera um tempo
}

void output4(){

     led4 = 1;                   //liga led azul
     delay_ms(300);              //espera um tempo
     led4 = 0;                   //desliga led azul
     delay_ms(300);              //espera um tempo
}

void sementee(){               //captura o valor de TMR0 como semente

   while(1){
             if(~but1){        //Se o botão (led1) é pressionado...
               semente = TMR0L;//valor de TMR0 é capturado
               break;          //quebra do loop
             }
     }
     TMR0ON_bit = 0;            //desliga o timer 0
     delay_ms(500);            //espera um pouco antes de iniciar o jogo

}

void verific(int num){         //verifica se os botões foram pressionados na sequência

     if(sequencia[cont] != num){ //se o jogador errou...
        flag[vez] = 0;           //muda a flag do jogador para 0 indicando o erro
     }
     cont++;                     //incrementa a contagem de botões pressionados

}

void lerbotao(){               //faz a leitura do apertar de botões
     while(1){
        if(~but1){             //se o botão 1 é pressionado...
             output1();        //pisca led vermelho
             verific(1);       //verifica se está de acordo com a sequência
        }

        if(~but2){             //se o botão 2 é pressionado...
             output2();        //pisca led amarelo
             verific(2);       //verifica se está de acordo com a sequência
        }

        if(~but3){             //se o botão 3 é pressionado...
             output3();        //pisca led verde
             verific(3);       //verifica se está de acordo com a sequência
        }

        if(~but4){              //se o botão 4 é pressionado...
             output4();         //pisca led azul
             verific(4);        //verifica se está de acordo com a sequência
        }

        if(cont == nivel){      //se a quantidade de botões pressionados é igual ao nível...
           break;               //para de ler botões
        }
       }

       cont = 0;               //zera a quantidade de botôes pressionados

}

//função que pisca todos os leds enquanto jogadores esperam anúcio do vencedor
void expectativa(){

    for(i = 0; i<8; i++){           //pisca todos os leds

                led1 = ~led1;
                led2 = ~led2;
                led3 = ~led3;
                led4 = ~led4;
                jog1 = ~jog1;
                jog2 = ~jog2;
                delay_ms(150);

     }

}


void resultado(){                           //mostra o resultado da rodada

      if(modo == 0){                        //se modo singleplayer...
      
         if(flag[0] == 1){                  //se o jogador acertou
         

            for(i = 0; i<6; i++){           //pisca led do jogador três vezes

                  jog1 = ~jog1;
                  delay_ms(150);

            }
            delay_ms(800);                  //espera um tempo para iniciar próximo nível
            nivel = nivel++;                //próximo nível
         }
         else{                              //se o jogador errou
         
            for(i = 0; i<6; i++){           //pisca led oposto do jogador 1 três vezes

                  jog2 = ~jog2;
                  delay_ms(150);

            }

            fim = 1;                        //indica o fim do jogo
         }
         
      }

      if(modo == 1){                        //se modo multiplayer...

         if(flag[0] == 1 && flag[1] == 1){  //se os dois acertaram...

            for(i = 0; i<6; i++){           //pisca led dos jogadores 2 vezes

                  jog1 = ~jog1;
                  jog2 = ~jog2;
                  delay_ms(150);

            }

            delay_ms(800);                  //espera um tempo para iniciar próximo nível
            nivel = nivel++;                //próximo nível
         }

         if(flag[0] == 0 && flag[1] == 1){  //se o jogador 1 errou...

            expectativa();                  // pisca todos os leds gerando expectativa

            for(i = 0; i<6; i++){          //pisca os leds do jogador 2

                  jog2 = ~jog2;
                  delay_ms(150);

            }

            fim = 1;                       //indica o fim do jogo


           }

         if(flag[0] == 1 && flag[1] == 0){  //se o jogador 2 errou...

            expectativa();                  //pisca todos os leds gerando expectativa

            for(i = 0; i<6; i++){           //pisca leds do jogador 1

                  jog1 = ~jog1;
                  delay_ms(150);

            }

            fim = 1;                       //indica o fim do jogo


         }

         if(flag[0] == 0 && flag[1] == 0){  //se os dois jogadores erraram...

            expectativa();                  //pisca todos os leds

             for(i = 0; i <6; i++){         //uma sequência indica o empate
              led1 = ~led1;
              delay_ms(100);
              led2 = ~led2;
              delay_ms(100);
              led3 = ~led3;
              delay_ms(100);
              led4 = ~led4;
              delay_ms(100);

              }

              fim = 1;                       //indica o fim do jogo

         }
     }

}

void zerar(){      //se o jogo foi zerado gera um sinal indicando vitória e o fim

     for(i = 0; i<4; i++){

                led1 = ~led1;
                delay_ms(100);
                led2 = ~led2;
                delay_ms(100);
                led3 = ~led3;
                delay_ms(100);
                led4 = ~led4;
                delay_ms(100);
                jog1 = ~jog1;
                delay_ms(100);
                jog2 = ~jog2;
                delay_ms(100);
                
                led1 = ~led1;
                delay_ms(100);
                led2 = ~led2;
                delay_ms(100);
                led3 = ~led3;
                delay_ms(100);
                led4 = ~led4;
                delay_ms(100);
                jog1 = ~jog1;
                delay_ms(100);
                jog2 = ~jog2;
                delay_ms(100);
                

     }

}
