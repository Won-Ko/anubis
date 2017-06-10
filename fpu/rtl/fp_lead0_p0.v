//==============================================================================
//      File:           $URL$
//      Version:        $Revision$
//      Author:         Jose Renau  (http://masc.cse.ucsc.edu/)
//                      John Burr
//      Copyright:      Copyright 2005-2008 UC Santa Cruz
//==============================================================================

//==============================================================================
//      Section:        License
//==============================================================================
//      Copyright (c) 2005-2008, Regents of the University of California
//      All rights reserved.
//
//      Redistribution and use in source and binary forms, with or without modification,
//      are permitted provided that the following conditions are met:
//
//              - Redistributions of source code must retain the above copyright notice,
//                      this list of conditions and the following disclaimer.
//              - Redistributions in binary form must reproduce the above copyright
//                      notice, this list of conditions and the following disclaimer
//                      in the documentation and/or other materials provided with the
//                      distribution.
//              - Neither the name of the University of California, Santa Cruz nor the
//                      names of its contributors may be used to endorse or promote
//                      products derived from this software without specific prior
//                      written permission.
//
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//      ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//      WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//      DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
//      ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//      LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//      ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//      SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//==============================================================================

/****************************************************************************
    Description

 PHASE 0 for lead0
 
 -Phase 0: shift leading 0 into upper 16 bits, and compute lead0
 
****************************************************************************/

`include "dfuncs.h"

module fp_lead0_p0
  (input  [64-1:0]         data
   ,output reg [5:0]       lead0_p0
   ,output reg [64-1:0]    normalized_p0
   );

  reg [5:0]         lead0;
  always @(*) begin
    casez(data[63:8])
      64'b1???????????????????????????????????????????????????????????????: begin lead0 = 6'd0; end
      64'b01??????????????????????????????????????????????????????????????: begin lead0 = 6'd1; end
      64'b001?????????????????????????????????????????????????????????????: begin lead0 = 6'd2; end
      64'b0001????????????????????????????????????????????????????????????: begin lead0 = 6'd3; end
      64'b00001???????????????????????????????????????????????????????????: begin lead0 = 6'd4; end
      64'b000001??????????????????????????????????????????????????????????: begin lead0 = 6'd5; end
      64'b0000001?????????????????????????????????????????????????????????: begin lead0 = 6'd6; end
      64'b00000001????????????????????????????????????????????????????????: begin lead0 = 6'd7; end
      64'b000000001???????????????????????????????????????????????????????: begin lead0 = 6'd8; end
      64'b0000000001??????????????????????????????????????????????????????: begin lead0 = 6'd9; end
      64'b00000000001?????????????????????????????????????????????????????: begin lead0 = 6'd10; end
      64'b000000000001????????????????????????????????????????????????????: begin lead0 = 6'd11; end
      64'b0000000000001???????????????????????????????????????????????????: begin lead0 = 6'd12; end
      64'b00000000000001??????????????????????????????????????????????????: begin lead0 = 6'd13; end
      64'b000000000000001?????????????????????????????????????????????????: begin lead0 = 6'd14; end
      64'b0000000000000001????????????????????????????????????????????????: begin lead0 = 6'd15; end
      64'b00000000000000001???????????????????????????????????????????????: begin lead0 = 6'd16; end
      64'b000000000000000001??????????????????????????????????????????????: begin lead0 = 6'd17; end
      64'b0000000000000000001?????????????????????????????????????????????: begin lead0 = 6'd18; end
      64'b00000000000000000001????????????????????????????????????????????: begin lead0 = 6'd19; end
      64'b000000000000000000001???????????????????????????????????????????: begin lead0 = 6'd20; end
      64'b0000000000000000000001??????????????????????????????????????????: begin lead0 = 6'd21; end
      64'b00000000000000000000001?????????????????????????????????????????: begin lead0 = 6'd22; end
      64'b000000000000000000000001????????????????????????????????????????: begin lead0 = 6'd23; end
      64'b0000000000000000000000001???????????????????????????????????????: begin lead0 = 6'd24; end
      64'b00000000000000000000000001??????????????????????????????????????: begin lead0 = 6'd25; end
      64'b000000000000000000000000001?????????????????????????????????????: begin lead0 = 6'd26; end
      64'b0000000000000000000000000001????????????????????????????????????: begin lead0 = 6'd27; end
      64'b00000000000000000000000000001???????????????????????????????????: begin lead0 = 6'd28; end
      64'b000000000000000000000000000001??????????????????????????????????: begin lead0 = 6'd29; end
      64'b0000000000000000000000000000001?????????????????????????????????: begin lead0 = 6'd30; end
      64'b00000000000000000000000000000001????????????????????????????????: begin lead0 = 6'd31; end
      64'b000000000000000000000000000000001???????????????????????????????: begin lead0 = 6'd32; end
      64'b0000000000000000000000000000000001??????????????????????????????: begin lead0 = 6'd33; end
      64'b00000000000000000000000000000000001?????????????????????????????: begin lead0 = 6'd34; end
      64'b000000000000000000000000000000000001????????????????????????????: begin lead0 = 6'd35; end
      64'b0000000000000000000000000000000000001???????????????????????????: begin lead0 = 6'd36; end
      64'b00000000000000000000000000000000000001??????????????????????????: begin lead0 = 6'd37; end
      64'b000000000000000000000000000000000000001?????????????????????????: begin lead0 = 6'd38; end
      64'b0000000000000000000000000000000000000001????????????????????????: begin lead0 = 6'd39; end
      64'b00000000000000000000000000000000000000001???????????????????????: begin lead0 = 6'd40; end
      64'b000000000000000000000000000000000000000001??????????????????????: begin lead0 = 6'd41; end
      64'b0000000000000000000000000000000000000000001?????????????????????: begin lead0 = 6'd42; end
      64'b00000000000000000000000000000000000000000001????????????????????: begin lead0 = 6'd43; end
      64'b000000000000000000000000000000000000000000001???????????????????: begin lead0 = 6'd44; end
      64'b0000000000000000000000000000000000000000000001??????????????????: begin lead0 = 6'd45; end
      64'b00000000000000000000000000000000000000000000001?????????????????: begin lead0 = 6'd46; end
      64'b000000000000000000000000000000000000000000000001????????????????: begin lead0 = 6'd47; end
      64'b0000000000000000000000000000000000000000000000001???????????????: begin lead0 = 6'd48; end
      64'b00000000000000000000000000000000000000000000000001??????????????: begin lead0 = 6'd49; end
      64'b000000000000000000000000000000000000000000000000001?????????????: begin lead0 = 6'd50; end
      64'b0000000000000000000000000000000000000000000000000001????????????: begin lead0 = 6'd51; end
      64'b00000000000000000000000000000000000000000000000000001???????????: begin lead0 = 6'd52; end
      64'b000000000000000000000000000000000000000000000000000001??????????: begin lead0 = 6'd53; end
      64'b0000000000000000000000000000000000000000000000000000001?????????: begin lead0 = 6'd54; end
      64'b00000000000000000000000000000000000000000000000000000001????????: begin lead0 = 6'd55; end
      64'b000000000000000000000000000000000000000000000000000000001???????: begin lead0 = 6'd56; end
      64'b0000000000000000000000000000000000000000000000000000000001??????: begin lead0 = 6'd57; end
      64'b00000000000000000000000000000000000000000000000000000000001?????: begin lead0 = 6'd58; end
      64'b000000000000000000000000000000000000000000000000000000000001????: begin lead0 = 6'd59; end
      64'b0000000000000000000000000000000000000000000000000000000000001???: begin lead0 = 6'd60; end
      64'b00000000000000000000000000000000000000000000000000000000000001??: begin lead0 = 6'd61; end
      64'b000000000000000000000000000000000000000000000000000000000000001?: begin lead0 = 6'd62; end
      64'b000000000000000000000000000000000000000000000000000000000000000?: begin lead0 = 6'd63; end
    endcase
  end

  always @(*) begin
    lead0_p0 = lead0;
  end
  
  reg [64-1:0]    normalized_p0_next;
  // normalized_p0_next will have leading 1 in top 16 bits
  always @(*) begin
    casez({data[63:48] != 16'b0,
           data[47:32] != 16'b0,
`ifndef ANUBIS_NOC_1
           data[31:16] != 16'b0,
`else
           data[31:16] == 16'b0,
`endif
           data[15:00] != 16'b0})
      4'b1???: normalized_p0_next = data;
      4'b01??: normalized_p0_next = data<<16;
      4'b001?: normalized_p0_next = data<<32;
      4'b000?: normalized_p0_next = data<<48;
    endcase
  end

  always @(*) begin
    normalized_p0 = normalized_p0_next;
  end
    
endmodule

