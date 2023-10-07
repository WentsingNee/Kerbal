
./test2:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	callq  *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	retq   

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 e2 2f 00 00    	pushq  0x2fe2(%rip)        # 4008 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 e4 2f 00 00    	jmpq   *0x2fe4(%rip)        # 4010 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000001030 <std::basic_ostream<char, std::char_traits<char> >::put(char)@plt>:
    1030:	ff 25 e2 2f 00 00    	jmpq   *0x2fe2(%rip)        # 4018 <std::basic_ostream<char, std::char_traits<char> >::put(char)@GLIBCXX_3.4>
    1036:	68 00 00 00 00       	pushq  $0x0
    103b:	e9 e0 ff ff ff       	jmpq   1020 <.plt>

0000000000001040 <memset@plt>:
    1040:	ff 25 da 2f 00 00    	jmpq   *0x2fda(%rip)        # 4020 <memset@GLIBC_2.2.5>
    1046:	68 01 00 00 00       	pushq  $0x1
    104b:	e9 d0 ff ff ff       	jmpq   1020 <.plt>

0000000000001050 <std::basic_ostream<char, std::char_traits<char> >::flush()@plt>:
    1050:	ff 25 d2 2f 00 00    	jmpq   *0x2fd2(%rip)        # 4028 <std::basic_ostream<char, std::char_traits<char> >::flush()@GLIBCXX_3.4>
    1056:	68 02 00 00 00       	pushq  $0x2
    105b:	e9 c0 ff ff ff       	jmpq   1020 <.plt>

0000000000001060 <__cxa_atexit@plt>:
    1060:	ff 25 ca 2f 00 00    	jmpq   *0x2fca(%rip)        # 4030 <__cxa_atexit@GLIBC_2.2.5>
    1066:	68 03 00 00 00       	pushq  $0x3
    106b:	e9 b0 ff ff ff       	jmpq   1020 <.plt>

0000000000001070 <operator delete(void*)@plt>:
    1070:	ff 25 c2 2f 00 00    	jmpq   *0x2fc2(%rip)        # 4038 <operator delete(void*)@GLIBCXX_3.4>
    1076:	68 04 00 00 00       	pushq  $0x4
    107b:	e9 a0 ff ff ff       	jmpq   1020 <.plt>

0000000000001080 <operator new(unsigned long)@plt>:
    1080:	ff 25 ba 2f 00 00    	jmpq   *0x2fba(%rip)        # 4040 <operator new(unsigned long)@GLIBCXX_3.4>
    1086:	68 05 00 00 00       	pushq  $0x5
    108b:	e9 90 ff ff ff       	jmpq   1020 <.plt>

0000000000001090 <std::ctype<char>::_M_widen_init() const@plt>:
    1090:	ff 25 b2 2f 00 00    	jmpq   *0x2fb2(%rip)        # 4048 <std::ctype<char>::_M_widen_init() const@GLIBCXX_3.4.11>
    1096:	68 06 00 00 00       	pushq  $0x6
    109b:	e9 80 ff ff ff       	jmpq   1020 <.plt>

00000000000010a0 <std::__throw_bad_cast()@plt>:
    10a0:	ff 25 aa 2f 00 00    	jmpq   *0x2faa(%rip)        # 4050 <std::__throw_bad_cast()@GLIBCXX_3.4>
    10a6:	68 07 00 00 00       	pushq  $0x7
    10ab:	e9 70 ff ff ff       	jmpq   1020 <.plt>

00000000000010b0 <std::ios_base::Init::Init()@plt>:
    10b0:	ff 25 a2 2f 00 00    	jmpq   *0x2fa2(%rip)        # 4058 <std::ios_base::Init::Init()@GLIBCXX_3.4>
    10b6:	68 08 00 00 00       	pushq  $0x8
    10bb:	e9 60 ff ff ff       	jmpq   1020 <.plt>

00000000000010c0 <std::basic_ostream<char, std::char_traits<char> >::operator<<(int)@plt>:
    10c0:	ff 25 9a 2f 00 00    	jmpq   *0x2f9a(%rip)        # 4060 <std::basic_ostream<char, std::char_traits<char> >::operator<<(int)@GLIBCXX_3.4>
    10c6:	68 09 00 00 00       	pushq  $0x9
    10cb:	e9 50 ff ff ff       	jmpq   1020 <.plt>

00000000000010d0 <_Unwind_Resume@plt>:
    10d0:	ff 25 92 2f 00 00    	jmpq   *0x2f92(%rip)        # 4068 <_Unwind_Resume@GCC_3.0>
    10d6:	68 0a 00 00 00       	pushq  $0xa
    10db:	e9 40 ff ff ff       	jmpq   1020 <.plt>

Disassembly of section .plt.got:

00000000000010e0 <__cxa_finalize@plt>:
    10e0:	ff 25 ea 2e 00 00    	jmpq   *0x2eea(%rip)        # 3fd0 <__cxa_finalize@GLIBC_2.2.5>
    10e6:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

00000000000010f0 <main.cold>:
    10f0:	4c 89 f7             	mov    %r14,%rdi
    10f3:	c5 f8 77             	vzeroupper 
    10f6:	e8 75 ff ff ff       	callq  1070 <operator delete(void*)@plt>
    10fb:	48 89 df             	mov    %rbx,%rdi
    10fe:	e8 cd ff ff ff       	callq  10d0 <_Unwind_Resume@plt>
    1103:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
    110a:	00 00 00 
    110d:	0f 1f 00             	nopl   (%rax)

0000000000001110 <main>:
    1110:	41 57                	push   %r15
    1112:	bf 28 00 00 00       	mov    $0x28,%edi
    1117:	41 56                	push   %r14
    1119:	41 55                	push   %r13
    111b:	41 54                	push   %r12
    111d:	55                   	push   %rbp
    111e:	53                   	push   %rbx
    111f:	48 81 ec d8 09 00 00 	sub    $0x9d8,%rsp
    1126:	e8 55 ff ff ff       	callq  1080 <operator new(unsigned long)@plt>
    112b:	48 c7 40 20 00 00 00 	movq   $0x0,0x20(%rax)
    1132:	00 
    1133:	c5 f9 ef c0          	vpxor  %xmm0,%xmm0,%xmm0
    1137:	48 89 e3             	mov    %rsp,%rbx
    113a:	ba c0 09 00 00       	mov    $0x9c0,%edx
    113f:	c5 fa 7f 00          	vmovdqu %xmm0,(%rax)
    1143:	c5 fa 7f 40 10       	vmovdqu %xmm0,0x10(%rax)
    1148:	31 f6                	xor    %esi,%esi
    114a:	48 89 df             	mov    %rbx,%rdi
    114d:	49 89 c6             	mov    %rax,%r14
    1150:	e8 eb fe ff ff       	callq  1040 <memset@plt>
    1155:	c7 04 24 71 15 00 00 	movl   $0x1571,(%rsp)
    115c:	48 c7 84 24 c0 09 00 	movq   $0x270,0x9c0(%rsp)
    1163:	00 70 02 00 00 
    1168:	b9 71 15 00 00       	mov    $0x1571,%ecx
    116d:	ba 01 00 00 00       	mov    $0x1,%edx
    1172:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1178:	89 c8                	mov    %ecx,%eax
    117a:	c1 e8 1e             	shr    $0x1e,%eax
    117d:	31 c8                	xor    %ecx,%eax
    117f:	69 c0 65 89 07 6c    	imul   $0x6c078965,%eax,%eax
    1185:	8d 0c 10             	lea    (%rax,%rdx,1),%ecx
    1188:	89 0c 93             	mov    %ecx,(%rbx,%rdx,4)
    118b:	48 ff c2             	inc    %rdx
    118e:	48 81 fa 70 02 00 00 	cmp    $0x270,%rdx
    1195:	75 e1                	jne    1178 <main+0x68>
    1197:	4d 89 f4             	mov    %r14,%r12
    119a:	4d 8d 6e 28          	lea    0x28(%r14),%r13
    119e:	4c 89 f5             	mov    %r14,%rbp
    11a1:	41 bf cd cc cc cc    	mov    $0xcccccccd,%r15d
    11a7:	eb 5d                	jmp    1206 <main+0xf6>
    11a9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    11b0:	48 89 d0             	mov    %rdx,%rax
    11b3:	48 ff c2             	inc    %rdx
    11b6:	8b 04 84             	mov    (%rsp,%rax,4),%eax
    11b9:	48 83 c5 04          	add    $0x4,%rbp
    11bd:	89 c1                	mov    %eax,%ecx
    11bf:	c1 e9 0b             	shr    $0xb,%ecx
    11c2:	31 c8                	xor    %ecx,%eax
    11c4:	89 c1                	mov    %eax,%ecx
    11c6:	c1 e1 07             	shl    $0x7,%ecx
    11c9:	81 e1 80 56 2c 9d    	and    $0x9d2c5680,%ecx
    11cf:	31 c8                	xor    %ecx,%eax
    11d1:	89 c1                	mov    %eax,%ecx
    11d3:	c1 e1 0f             	shl    $0xf,%ecx
    11d6:	81 e1 00 00 c6 ef    	and    $0xefc60000,%ecx
    11dc:	31 c8                	xor    %ecx,%eax
    11de:	89 c1                	mov    %eax,%ecx
    11e0:	c1 e9 12             	shr    $0x12,%ecx
    11e3:	31 c8                	xor    %ecx,%eax
    11e5:	89 c1                	mov    %eax,%ecx
    11e7:	49 0f af cf          	imul   %r15,%rcx
    11eb:	48 89 94 24 c0 09 00 	mov    %rdx,0x9c0(%rsp)
    11f2:	00 
    11f3:	48 c1 e9 23          	shr    $0x23,%rcx
    11f7:	8d 0c 89             	lea    (%rcx,%rcx,4),%ecx
    11fa:	01 c9                	add    %ecx,%ecx
    11fc:	29 c8                	sub    %ecx,%eax
    11fe:	89 45 fc             	mov    %eax,-0x4(%rbp)
    1201:	4c 39 ed             	cmp    %r13,%rbp
    1204:	74 1a                	je     1220 <main+0x110>
    1206:	48 81 fa 70 02 00 00 	cmp    $0x270,%rdx
    120d:	75 a1                	jne    11b0 <main+0xa0>
    120f:	48 89 df             	mov    %rbx,%rdi
    1212:	e8 e9 01 00 00       	callq  1400 <void kerbal::random::detail::avx2::mt_twist<624ul, 397ul, 31ul, 2567483615u>(unsigned int*)>
    1217:	ba 01 00 00 00       	mov    $0x1,%edx
    121c:	31 c0                	xor    %eax,%eax
    121e:	eb 96                	jmp    11b6 <main+0xa6>
    1220:	4c 8d 3d 99 2e 00 00 	lea    0x2e99(%rip),%r15        # 40c0 <std::cout@@GLIBCXX_3.4>
    1227:	eb 24                	jmp    124d <main+0x13d>
    1229:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1230:	0f be 75 43          	movsbl 0x43(%rbp),%esi
    1234:	48 89 df             	mov    %rbx,%rdi
    1237:	e8 f4 fd ff ff       	callq  1030 <std::basic_ostream<char, std::char_traits<char> >::put(char)@plt>
    123c:	48 89 c7             	mov    %rax,%rdi
    123f:	e8 0c fe ff ff       	callq  1050 <std::basic_ostream<char, std::char_traits<char> >::flush()@plt>
    1244:	49 83 c4 04          	add    $0x4,%r12
    1248:	4d 39 e5             	cmp    %r12,%r13
    124b:	74 54                	je     12a1 <main+0x191>
    124d:	41 8b 34 24          	mov    (%r12),%esi
    1251:	4c 89 ff             	mov    %r15,%rdi
    1254:	e8 67 fe ff ff       	callq  10c0 <std::basic_ostream<char, std::char_traits<char> >::operator<<(int)@plt>
    1259:	48 89 c3             	mov    %rax,%rbx
    125c:	48 8b 00             	mov    (%rax),%rax
    125f:	48 8b 40 e8          	mov    -0x18(%rax),%rax
    1263:	48 8b ac 03 f0 00 00 	mov    0xf0(%rbx,%rax,1),%rbp
    126a:	00 
    126b:	48 85 ed             	test   %rbp,%rbp
    126e:	74 4d                	je     12bd <main+0x1ad>
    1270:	80 7d 38 00          	cmpb   $0x0,0x38(%rbp)
    1274:	75 ba                	jne    1230 <main+0x120>
    1276:	48 89 ef             	mov    %rbp,%rdi
    1279:	e8 12 fe ff ff       	callq  1090 <std::ctype<char>::_M_widen_init() const@plt>
    127e:	48 8b 45 00          	mov    0x0(%rbp),%rax
    1282:	48 8d 3d 67 01 00 00 	lea    0x167(%rip),%rdi        # 13f0 <std::ctype<char>::do_widen(char) const>
    1289:	48 8b 40 30          	mov    0x30(%rax),%rax
    128d:	be 0a 00 00 00       	mov    $0xa,%esi
    1292:	48 39 f8             	cmp    %rdi,%rax
    1295:	74 9d                	je     1234 <main+0x124>
    1297:	48 89 ef             	mov    %rbp,%rdi
    129a:	ff d0                	callq  *%rax
    129c:	0f be f0             	movsbl %al,%esi
    129f:	eb 93                	jmp    1234 <main+0x124>
    12a1:	4c 89 f7             	mov    %r14,%rdi
    12a4:	e8 c7 fd ff ff       	callq  1070 <operator delete(void*)@plt>
    12a9:	48 81 c4 d8 09 00 00 	add    $0x9d8,%rsp
    12b0:	5b                   	pop    %rbx
    12b1:	5d                   	pop    %rbp
    12b2:	41 5c                	pop    %r12
    12b4:	41 5d                	pop    %r13
    12b6:	41 5e                	pop    %r14
    12b8:	31 c0                	xor    %eax,%eax
    12ba:	41 5f                	pop    %r15
    12bc:	c3                   	retq   
    12bd:	e8 de fd ff ff       	callq  10a0 <std::__throw_bad_cast()@plt>
    12c2:	48 89 c3             	mov    %rax,%rbx
    12c5:	e9 26 fe ff ff       	jmpq   10f0 <main.cold>
    12ca:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000012d0 <_GLOBAL__sub_I_main>:
    12d0:	53                   	push   %rbx
    12d1:	48 8d 1d f9 2e 00 00 	lea    0x2ef9(%rip),%rbx        # 41d1 <std::__ioinit>
    12d8:	48 89 df             	mov    %rbx,%rdi
    12db:	e8 d0 fd ff ff       	callq  10b0 <std::ios_base::Init::Init()@plt>
    12e0:	48 8b 3d 11 2d 00 00 	mov    0x2d11(%rip),%rdi        # 3ff8 <std::ios_base::Init::~Init()@GLIBCXX_3.4>
    12e7:	48 89 de             	mov    %rbx,%rsi
    12ea:	48 8d 15 87 2d 00 00 	lea    0x2d87(%rip),%rdx        # 4078 <__dso_handle>
    12f1:	5b                   	pop    %rbx
    12f2:	e9 69 fd ff ff       	jmpq   1060 <__cxa_atexit@plt>
    12f7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
    12fe:	00 00 

0000000000001300 <_start>:
    1300:	f3 0f 1e fa          	endbr64 
    1304:	31 ed                	xor    %ebp,%ebp
    1306:	49 89 d1             	mov    %rdx,%r9
    1309:	5e                   	pop    %rsi
    130a:	48 89 e2             	mov    %rsp,%rdx
    130d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1311:	50                   	push   %rax
    1312:	54                   	push   %rsp
    1313:	4c 8d 05 76 03 00 00 	lea    0x376(%rip),%r8        # 1690 <__libc_csu_fini>
    131a:	48 8d 0d ff 02 00 00 	lea    0x2ff(%rip),%rcx        # 1620 <__libc_csu_init>
    1321:	48 8d 3d e8 fd ff ff 	lea    -0x218(%rip),%rdi        # 1110 <main>
    1328:	ff 15 b2 2c 00 00    	callq  *0x2cb2(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.2.5>
    132e:	f4                   	hlt    
    132f:	90                   	nop

0000000000001330 <deregister_tm_clones>:
    1330:	48 8d 3d 51 2d 00 00 	lea    0x2d51(%rip),%rdi        # 4088 <__TMC_END__>
    1337:	48 8d 05 4a 2d 00 00 	lea    0x2d4a(%rip),%rax        # 4088 <__TMC_END__>
    133e:	48 39 f8             	cmp    %rdi,%rax
    1341:	74 15                	je     1358 <deregister_tm_clones+0x28>
    1343:	48 8b 05 8e 2c 00 00 	mov    0x2c8e(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable>
    134a:	48 85 c0             	test   %rax,%rax
    134d:	74 09                	je     1358 <deregister_tm_clones+0x28>
    134f:	ff e0                	jmpq   *%rax
    1351:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1358:	c3                   	retq   
    1359:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001360 <register_tm_clones>:
    1360:	48 8d 3d 21 2d 00 00 	lea    0x2d21(%rip),%rdi        # 4088 <__TMC_END__>
    1367:	48 8d 35 1a 2d 00 00 	lea    0x2d1a(%rip),%rsi        # 4088 <__TMC_END__>
    136e:	48 29 fe             	sub    %rdi,%rsi
    1371:	48 89 f0             	mov    %rsi,%rax
    1374:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1378:	48 c1 f8 03          	sar    $0x3,%rax
    137c:	48 01 c6             	add    %rax,%rsi
    137f:	48 d1 fe             	sar    %rsi
    1382:	74 14                	je     1398 <register_tm_clones+0x38>
    1384:	48 8b 05 65 2c 00 00 	mov    0x2c65(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable>
    138b:	48 85 c0             	test   %rax,%rax
    138e:	74 08                	je     1398 <register_tm_clones+0x38>
    1390:	ff e0                	jmpq   *%rax
    1392:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1398:	c3                   	retq   
    1399:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000013a0 <__do_global_dtors_aux>:
    13a0:	f3 0f 1e fa          	endbr64 
    13a4:	80 3d 25 2e 00 00 00 	cmpb   $0x0,0x2e25(%rip)        # 41d0 <completed.0>
    13ab:	75 2b                	jne    13d8 <__do_global_dtors_aux+0x38>
    13ad:	55                   	push   %rbp
    13ae:	48 83 3d 1a 2c 00 00 	cmpq   $0x0,0x2c1a(%rip)        # 3fd0 <__cxa_finalize@GLIBC_2.2.5>
    13b5:	00 
    13b6:	48 89 e5             	mov    %rsp,%rbp
    13b9:	74 0c                	je     13c7 <__do_global_dtors_aux+0x27>
    13bb:	48 8b 3d b6 2c 00 00 	mov    0x2cb6(%rip),%rdi        # 4078 <__dso_handle>
    13c2:	e8 19 fd ff ff       	callq  10e0 <__cxa_finalize@plt>
    13c7:	e8 64 ff ff ff       	callq  1330 <deregister_tm_clones>
    13cc:	c6 05 fd 2d 00 00 01 	movb   $0x1,0x2dfd(%rip)        # 41d0 <completed.0>
    13d3:	5d                   	pop    %rbp
    13d4:	c3                   	retq   
    13d5:	0f 1f 00             	nopl   (%rax)
    13d8:	c3                   	retq   
    13d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000013e0 <frame_dummy>:
    13e0:	f3 0f 1e fa          	endbr64 
    13e4:	e9 77 ff ff ff       	jmpq   1360 <register_tm_clones>
    13e9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000013f0 <std::ctype<char>::do_widen(char) const>:
    13f0:	89 f0                	mov    %esi,%eax
    13f2:	c3                   	retq   
    13f3:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
    13fa:	00 00 00 
    13fd:	0f 1f 00             	nopl   (%rax)

0000000000001400 <void kerbal::random::detail::avx2::mt_twist<624ul, 397ul, 31ul, 2567483615u>(unsigned int*)>:
    1400:	48 b9 00 00 00 80 00 	movabs $0x8000000080000000,%rcx
    1407:	00 00 80 
    140a:	c4 e1 f9 6e f1       	vmovq  %rcx,%xmm6
    140f:	48 b9 01 00 00 00 01 	movabs $0x100000001,%rcx
    1416:	00 00 00 
    1419:	c4 e1 f9 6e f9       	vmovq  %rcx,%xmm7
    141e:	48 b9 df b0 08 99 df 	movabs $0x9908b0df9908b0df,%rcx
    1425:	b0 08 99 
    1428:	c4 e2 7d 59 d6       	vpbroadcastq %xmm6,%ymm2
    142d:	c4 e1 f9 6e f1       	vmovq  %rcx,%xmm6
    1432:	48 89 f8             	mov    %rdi,%rax
    1435:	48 8d b7 80 03 00 00 	lea    0x380(%rdi),%rsi
    143c:	48 89 fa             	mov    %rdi,%rdx
    143f:	c4 e2 7d 59 e7       	vpbroadcastq %xmm7,%ymm4
    1444:	c5 d1 ef ed          	vpxor  %xmm5,%xmm5,%xmm5
    1448:	c4 e2 7d 59 de       	vpbroadcastq %xmm6,%ymm3
    144d:	0f 1f 00             	nopl   (%rax)
    1450:	c5 ed df 4a 04       	vpandn 0x4(%rdx),%ymm2,%ymm1
    1455:	c5 ed db 02          	vpand  (%rdx),%ymm2,%ymm0
    1459:	48 83 c2 20          	add    $0x20,%rdx
    145d:	c5 fd eb c1          	vpor   %ymm1,%ymm0,%ymm0
    1461:	c5 f5 72 d0 01       	vpsrld $0x1,%ymm0,%ymm1
    1466:	c5 fd db c4          	vpand  %ymm4,%ymm0,%ymm0
    146a:	c5 f5 ef 8a 14 06 00 	vpxor  0x614(%rdx),%ymm1,%ymm1
    1471:	00 
    1472:	c5 d5 fa c0          	vpsubd %ymm0,%ymm5,%ymm0
    1476:	c5 fd db c3          	vpand  %ymm3,%ymm0,%ymm0
    147a:	c5 fd ef c1          	vpxor  %ymm1,%ymm0,%ymm0
    147e:	c5 fe 7f 42 e0       	vmovdqu %ymm0,-0x20(%rdx)
    1483:	48 39 f2             	cmp    %rsi,%rdx
    1486:	75 c8                	jne    1450 <void kerbal::random::detail::avx2::mt_twist<624ul, 397ul, 31ul, 2567483615u>(unsigned int*)+0x50>
    1488:	44 8b 87 80 03 00 00 	mov    0x380(%rdi),%r8d
    148f:	4c 8d 97 8c 03 00 00 	lea    0x38c(%rdi),%r10
    1496:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
    149d:	00 00 00 
    14a0:	44 89 c1             	mov    %r8d,%ecx
    14a3:	44 8b 42 04          	mov    0x4(%rdx),%r8d
    14a7:	81 e1 00 00 00 80    	and    $0x80000000,%ecx
    14ad:	44 89 c6             	mov    %r8d,%esi
    14b0:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    14b6:	09 ce                	or     %ecx,%esi
    14b8:	89 f1                	mov    %esi,%ecx
    14ba:	d1 e9                	shr    %ecx
    14bc:	33 8a 34 06 00 00    	xor    0x634(%rdx),%ecx
    14c2:	41 89 c9             	mov    %ecx,%r9d
    14c5:	41 81 f1 df b0 08 99 	xor    $0x9908b0df,%r9d
    14cc:	83 e6 01             	and    $0x1,%esi
    14cf:	41 0f 45 c9          	cmovne %r9d,%ecx
    14d3:	48 83 c2 04          	add    $0x4,%rdx
    14d7:	89 4a fc             	mov    %ecx,-0x4(%rdx)
    14da:	49 39 d2             	cmp    %rdx,%r10
    14dd:	75 c1                	jne    14a0 <void kerbal::random::detail::avx2::mt_twist<624ul, 397ul, 31ul, 2567483615u>(unsigned int*)+0xa0>
    14df:	48 ba 00 00 00 80 00 	movabs $0x8000000080000000,%rdx
    14e6:	00 00 80 
    14e9:	c4 e1 f9 6e fa       	vmovq  %rdx,%xmm7
    14ee:	48 ba 01 00 00 00 01 	movabs $0x100000001,%rdx
    14f5:	00 00 00 
    14f8:	c4 e2 7d 59 d7       	vpbroadcastq %xmm7,%ymm2
    14fd:	c4 e1 f9 6e fa       	vmovq  %rdx,%xmm7
    1502:	48 ba df b0 08 99 df 	movabs $0x9908b0df9908b0df,%rdx
    1509:	b0 08 99 
    150c:	c4 e1 f9 6e f2       	vmovq  %rdx,%xmm6
    1511:	48 8d 8f 20 06 00 00 	lea    0x620(%rdi),%rcx
    1518:	c4 e2 7d 59 e7       	vpbroadcastq %xmm7,%ymm4
    151d:	c5 d1 ef ed          	vpxor  %xmm5,%xmm5,%xmm5
    1521:	c4 e2 7d 59 de       	vpbroadcastq %xmm6,%ymm3
    1526:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
    152d:	00 00 00 
    1530:	c5 ed df 88 90 03 00 	vpandn 0x390(%rax),%ymm2,%ymm1
    1537:	00 
    1538:	c5 ed db 80 8c 03 00 	vpand  0x38c(%rax),%ymm2,%ymm0
    153f:	00 
    1540:	48 83 c0 20          	add    $0x20,%rax
    1544:	c5 fd eb c1          	vpor   %ymm1,%ymm0,%ymm0
    1548:	c5 f5 72 d0 01       	vpsrld $0x1,%ymm0,%ymm1
    154d:	c5 fd db c4          	vpand  %ymm4,%ymm0,%ymm0
    1551:	c5 f5 ef 48 e0       	vpxor  -0x20(%rax),%ymm1,%ymm1
    1556:	c5 d5 fa c0          	vpsubd %ymm0,%ymm5,%ymm0
    155a:	c5 fd db c3          	vpand  %ymm3,%ymm0,%ymm0
    155e:	c5 fd ef c1          	vpxor  %ymm1,%ymm0,%ymm0
    1562:	c5 fe 7f 80 6c 03 00 	vmovdqu %ymm0,0x36c(%rax)
    1569:	00 
    156a:	48 39 c8             	cmp    %rcx,%rax
    156d:	75 c1                	jne    1530 <void kerbal::random::detail::avx2::mt_twist<624ul, 397ul, 31ul, 2567483615u>(unsigned int*)+0x130>
    156f:	b8 ff ff ff 7f       	mov    $0x7fffffff,%eax
    1574:	c5 f9 6e c0          	vmovd  %eax,%xmm0
    1578:	b8 00 00 00 80       	mov    $0x80000000,%eax
    157d:	c5 f9 6e c8          	vmovd  %eax,%xmm1
    1581:	c5 f9 70 c0 00       	vpshufd $0x0,%xmm0,%xmm0
    1586:	c5 f9 70 c9 00       	vpshufd $0x0,%xmm1,%xmm1
    158b:	c5 f9 db 87 b0 09 00 	vpand  0x9b0(%rdi),%xmm0,%xmm0
    1592:	00 
    1593:	c5 f1 db 8f ac 09 00 	vpand  0x9ac(%rdi),%xmm1,%xmm1
    159a:	00 
    159b:	b8 01 00 00 00       	mov    $0x1,%eax
    15a0:	c5 f9 eb c1          	vpor   %xmm1,%xmm0,%xmm0
    15a4:	c5 f9 6e c8          	vmovd  %eax,%xmm1
    15a8:	c5 f9 70 c9 00       	vpshufd $0x0,%xmm1,%xmm1
    15ad:	b8 df b0 08 99       	mov    $0x9908b0df,%eax
    15b2:	8b 97 bc 09 00 00    	mov    0x9bc(%rdi),%edx
    15b8:	c5 e9 72 d0 01       	vpsrld $0x1,%xmm0,%xmm2
    15bd:	c5 f9 db c1          	vpand  %xmm1,%xmm0,%xmm0
    15c1:	c5 f9 6e c8          	vmovd  %eax,%xmm1
    15c5:	8b 07                	mov    (%rdi),%eax
    15c7:	81 e2 00 00 00 80    	and    $0x80000000,%edx
    15cd:	25 ff ff ff 7f       	and    $0x7fffffff,%eax
    15d2:	09 c2                	or     %eax,%edx
    15d4:	89 d0                	mov    %edx,%eax
    15d6:	d1 e8                	shr    %eax
    15d8:	33 87 30 06 00 00    	xor    0x630(%rdi),%eax
    15de:	89 c1                	mov    %eax,%ecx
    15e0:	81 f1 df b0 08 99    	xor    $0x9908b0df,%ecx
    15e6:	c5 e1 ef db          	vpxor  %xmm3,%xmm3,%xmm3
    15ea:	83 e2 01             	and    $0x1,%edx
    15ed:	c5 e9 ef 97 20 06 00 	vpxor  0x620(%rdi),%xmm2,%xmm2
    15f4:	00 
    15f5:	c5 f9 76 c3          	vpcmpeqd %xmm3,%xmm0,%xmm0
    15f9:	0f 45 c1             	cmovne %ecx,%eax
    15fc:	c5 f9 70 c9 00       	vpshufd $0x0,%xmm1,%xmm1
    1601:	c5 e9 ef c9          	vpxor  %xmm1,%xmm2,%xmm1
    1605:	89 87 bc 09 00 00    	mov    %eax,0x9bc(%rdi)
    160b:	c4 e3 71 4c c2 00    	vpblendvb %xmm0,%xmm2,%xmm1,%xmm0
    1611:	c5 fa 7f 87 ac 09 00 	vmovdqu %xmm0,0x9ac(%rdi)
    1618:	00 
    1619:	c5 f8 77             	vzeroupper 
    161c:	c3                   	retq   
    161d:	0f 1f 00             	nopl   (%rax)

0000000000001620 <__libc_csu_init>:
    1620:	f3 0f 1e fa          	endbr64 
    1624:	41 57                	push   %r15
    1626:	4c 8d 3d 6b 27 00 00 	lea    0x276b(%rip),%r15        # 3d98 <__frame_dummy_init_array_entry>
    162d:	41 56                	push   %r14
    162f:	49 89 d6             	mov    %rdx,%r14
    1632:	41 55                	push   %r13
    1634:	49 89 f5             	mov    %rsi,%r13
    1637:	41 54                	push   %r12
    1639:	41 89 fc             	mov    %edi,%r12d
    163c:	55                   	push   %rbp
    163d:	48 8d 2d 64 27 00 00 	lea    0x2764(%rip),%rbp        # 3da8 <__do_global_dtors_aux_fini_array_entry>
    1644:	53                   	push   %rbx
    1645:	4c 29 fd             	sub    %r15,%rbp
    1648:	48 83 ec 08          	sub    $0x8,%rsp
    164c:	e8 af f9 ff ff       	callq  1000 <_init>
    1651:	48 c1 fd 03          	sar    $0x3,%rbp
    1655:	74 1f                	je     1676 <__libc_csu_init+0x56>
    1657:	31 db                	xor    %ebx,%ebx
    1659:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1660:	4c 89 f2             	mov    %r14,%rdx
    1663:	4c 89 ee             	mov    %r13,%rsi
    1666:	44 89 e7             	mov    %r12d,%edi
    1669:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    166d:	48 83 c3 01          	add    $0x1,%rbx
    1671:	48 39 dd             	cmp    %rbx,%rbp
    1674:	75 ea                	jne    1660 <__libc_csu_init+0x40>
    1676:	48 83 c4 08          	add    $0x8,%rsp
    167a:	5b                   	pop    %rbx
    167b:	5d                   	pop    %rbp
    167c:	41 5c                	pop    %r12
    167e:	41 5d                	pop    %r13
    1680:	41 5e                	pop    %r14
    1682:	41 5f                	pop    %r15
    1684:	c3                   	retq   
    1685:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
    168c:	00 00 00 00 

0000000000001690 <__libc_csu_fini>:
    1690:	f3 0f 1e fa          	endbr64 
    1694:	c3                   	retq   

Disassembly of section .fini:

0000000000001698 <_fini>:
    1698:	f3 0f 1e fa          	endbr64 
    169c:	48 83 ec 08          	sub    $0x8,%rsp
    16a0:	48 83 c4 08          	add    $0x8,%rsp
    16a4:	c3                   	retq   
