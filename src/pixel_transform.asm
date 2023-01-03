global sepia_filter_asm

section .rodata
 align 16
    v1: dd 0.131, 0.168, 0.189, 0.00
    v2: dd 0.543, 0.686, 0.769, 0.00
    v3: dd 0.272, 0.349, 0.393, 0.00
    max_rgb: dd 0xFF, 0xFF, 0xFF, 0xFF
;rdi
section .text
    sepia_filter_asm:
     jmp filter
    
    filter:
     push rdi

     push rdi
     call add_vectors
     pop rdi
     call shuffle_vector_batch_1 
     push rdi
  call multi_vectors
  pop rdi
  add rdi, 16
 
     push rdi
     call add_vectors
     pop rdi
     call shuffle_vector_batch_2 
     push rdi
  call multi_vectors
  pop rdi
  add rdi, 16
 
     push rdi
     call add_vectors
     pop rdi
     call shuffle_vector_batch_3 
     push rdi
  call multi_vectors
  pop rdi
  pop rdi
     ret
    
    ;rdi: order of matrix parameters to shuffle , like [c11 c21 c31 c11],...
    ;rsi: order of matrix values to shuffle, like [b0 b0 b0 b1],...
    add_vectors:
     ;add vector params to registers
     movaps xmm0, [v1] 
     movaps xmm1, [v2]
     movaps xmm2, [v3]
    
     ;add vector values to register
     movups xmm3, [rdi] 
     movups xmm4, [rdi+4] 
     movups xmm5, [rdi+8]
    
     cvtdq2ps xmm3, xmm3
     cvtdq2ps xmm4, xmm4
     cvtdq2ps xmm5, xmm5
     ret
    shuffle_vector_batch_1:
     ;shuffle vector params, depend on batch
     shufps xmm0, xmm0, 0x18
     shufps xmm1, xmm1, 0x18
     shufps xmm2, xmm2, 0x18
    
     ;shuffle vector values, independent on batch, always x1 x1 x1 x2
     ;like b1 b1 b1 b2, g1 g1 g1 g2, r1 r1 r1 r2, ...
     shufps xmm3, xmm3, 0xc0
     shufps xmm4, xmm4, 0xc0
     shufps xmm5, xmm5, 0xc0
     ret
    shuffle_vector_batch_2:
     ;shuffle vector params, depend on batch
     shufps xmm0, xmm0, 0x61
     shufps xmm1, xmm1, 0x61
     shufps xmm2, xmm2, 0x61
    
     ;shuffle vector values, independent on batch, always x1 x1 x1 x2
     ;like b1 b1 b1 b2, g1 g1 g1 g2, r1 r1 r1 r2, ...
     shufps xmm3, xmm3, 0xc0
     shufps xmm4, xmm4, 0xc0
     shufps xmm5, xmm5, 0xc0
     ret
     
    shuffle_vector_batch_3:
     ;shuffle vector params, depend on batch
     shufps xmm0, xmm0, 0x84
     shufps xmm1, xmm1, 0x84
     shufps xmm2, xmm2, 0x84
    
     ;shuffle vector values, independent on batch, always x1 x1 x1 x2
     ;like b1 b1 b1 b2, g1 g1 g1 g2, r1 r1 r1 r2, ...
     shufps xmm3, xmm3, 0xc0
     shufps xmm4, xmm4, 0xc0
     shufps xmm5, xmm5, 0xc0
     ret
    
    multi_vectors:
     mulps xmm3, xmm0
     mulps xmm4, xmm1
     mulps xmm5, xmm2
     addps xmm3, xmm4
     addps xmm3, xmm5
     cvtps2dq xmm3, xmm3
     pminud xmm3, [max_rgb]
     movaps [rdi], xmm3;
     ret