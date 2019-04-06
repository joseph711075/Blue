.class public BlueProject
.super java/lang/Object

.field private static _runTimer LRunTimer;
.field private static _standardIn LPascalTextIn;


.field private static i I
.field private static j I
.field private static k I
.field private static N I
.field private static M I
.field private static beta5x F
.field private static alpha F
.field private static cna F


.method public <init>()V

	aload_0
	invokenonvirtual    java/lang/Object/<init>()V
	return

.limit locals 1
.limit stack 1
.end method


.method private static fun(II)I

	iload_0
	iload_1
	iadd
	istore_2


;printf("value of sum: %d\n",sum)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "value of sum: %d\n"
	iconst_1
	anewarray    java/lang/Object
	dup
	iconst_0
	iload_2
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop


	iload_2
	ireturn


.limit stack 10
.limit locals 10
.end method
.method private static fun1(FF)F

	fload_0
	fload_1
	fadd
	fstore_2


;printf("value of sum: %f\n",sum)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "value of sum: %f\n"
	iconst_1
	anewarray    java/lang/Object
	dup
	iconst_0
	fload_2
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop


	fload_2
	freturn


.limit stack 10
.limit locals 10
.end method

.method public static main([Ljava/lang/String;)V

	new RunTimer
	dup
	invokenonvirtual RunTimer/<init>()V
	putstatic        BlueProject/_runTimer LRunTimer;
	new PascalTextIn
	dup
	invokenonvirtual PascalTextIn/<init>()V
	putstatic        BlueProject/_standardIn LPascalTextIn;

; i=23

	ldc	23
	putstatic	BlueProject/i I


;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; j=i

	getstatic	BlueProject/i I
	putstatic	BlueProject/j I


;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; i=-2+3*j

	ldc	2
	ineg
	ldc	3
	getstatic	BlueProject/j I
	imul
	iadd
	putstatic	BlueProject/i I


;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; i=j

	getstatic	BlueProject/j I
	putstatic	BlueProject/i I


;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; N=3

	ldc	3
	putstatic	BlueProject/N I


;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; M=3

	ldc	3
	putstatic	BlueProject/M I


;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; alpha=91.33

	ldc	91.33
	putstatic	BlueProject/alpha F


;printf("cna = %f, beta5x = %f, alpha = %f\n",cna,beta5x,alpha)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "cna = %f, beta5x = %f, alpha = %f\n"
	iconst_3
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/cna F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/beta5x F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/alpha F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; beta5x=alpha

	getstatic	BlueProject/alpha F
	putstatic	BlueProject/beta5x F


;printf("cna = %f, beta5x = %f, alpha = %f\n",cna,beta5x,alpha)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "cna = %f, beta5x = %f, alpha = %f\n"
	iconst_3
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/cna F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/beta5x F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/alpha F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; beta5x=alpha/3.7-alpha*2.88

	getstatic	BlueProject/alpha F
	ldc	3.7
	fdiv
	getstatic	BlueProject/alpha F
	ldc	2.88
	fmul
	fsub
	putstatic	BlueProject/beta5x F


;printf("cna = %f, beta5x = %f, alpha = %f\n",cna,beta5x,alpha)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "cna = %f, beta5x = %f, alpha = %f\n"
	iconst_3
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/cna F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/beta5x F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/alpha F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; beta5x=8.45*(alpha+9.12)

	ldc	8.45
	getstatic	BlueProject/alpha F
	ldc	9.12
	fadd
	fmul
	putstatic	BlueProject/beta5x F


;printf("cna = %f, beta5x = %f, alpha = %f\n",cna,beta5x,alpha)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "cna = %f, beta5x = %f, alpha = %f\n"
	iconst_3
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/cna F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/beta5x F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/alpha F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; j=j+1

	getstatic	BlueProject/j I
	ldc	1
	iadd
	putstatic	BlueProject/j I

; WHEN(j==24){j=6;}


; WHEN(j==24){j=6;}

	getstatic	BlueProject/j I
	ldc	24
	if_icmpeq	L000
	iconst_0
	 goto	L001
L000:
	iconst_1
L001:
	ifeq	L002

; j=6

	ldc	6
	putstatic	BlueProject/j I

L002:


; LOOP(j<=10){j=j+1;}


L003:


; LOOP(j<=10){j=j+1;}

	getstatic	BlueProject/j I
	ldc	10
	if_icmple	L004
	iconst_0
	 goto	L005
L004:
	iconst_1
L005:
	ifeq	L006

; j=j+1

	getstatic	BlueProject/j I
	ldc	1
	iadd
	putstatic	BlueProject/j I

	goto	L003


L006:



;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop


	getstatic	BlueProject/i I
	getstatic	BlueProject/j I
	invokestatic	BlueProject/fun(II)I
	putstatic	BlueProject/k I



;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop


	getstatic	BlueProject/k I
	getstatic	BlueProject/M I
	invokestatic	BlueProject/fun(II)I
	putstatic	BlueProject/k I



;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop


	getstatic	BlueProject/k I
	getstatic	BlueProject/N I
	invokestatic	BlueProject/fun(II)I
	putstatic	BlueProject/k I



;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop




;printf("cna = %f, beta5x = %f, alpha = %f\n",cna,beta5x,alpha)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "cna = %f, beta5x = %f, alpha = %f\n"
	iconst_3
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/cna F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/beta5x F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/alpha F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop


	getstatic	BlueProject/beta5x F
	getstatic	BlueProject/alpha F
	invokestatic	BlueProject/fun1(FF)F
	putstatic	BlueProject/cna F



;printf("cna = %f, beta5x = %f, alpha = %f\n",cna,beta5x,alpha)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "cna = %f, beta5x = %f, alpha = %f\n"
	iconst_3
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/cna F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/beta5x F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/alpha F
	invokestatic  java/lang/Float.valueOf(F)Ljava/lang/Float;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; i=2*4+10*2

	ldc	2
	ldc	4
	imul
	ldc	10
	ldc	2
	imul
	iadd
	putstatic	BlueProject/i I


;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; j=5+(5+3)*4

	ldc	5
	ldc	5
	ldc	3
	iadd
	ldc	4
	imul
	iadd
	putstatic	BlueProject/j I


;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



; k=3+4*4+6

	ldc	3
	ldc	4
	ldc	4
	imul
	iadd
	ldc	6
	iadd
	putstatic	BlueProject/k I


;printf("i = %d, j = %d, k = %d, N = %d, M = %d\n",i,j,k,N,M)
	getstatic    java/lang/System/out Ljava/io/PrintStream;
	ldc          "i = %d, j = %d, k = %d, N = %d, M = %d\n"
	iconst_5
	anewarray    java/lang/Object
	dup
	iconst_0
	getstatic	BlueProject/i I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_1
	getstatic	BlueProject/j I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_2
	getstatic	BlueProject/k I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_3
	getstatic	BlueProject/N I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	dup
	iconst_4
	getstatic	BlueProject/M I
	invokestatic  java/lang/Integer.valueOf(I)Ljava/lang/Integer;
	aastore
	invokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;
	pop



	getstatic     BlueProject/_runTimer LRunTimer;
	invokevirtual RunTimer.printElapsedTime()V

	return

.limit locals 16
.limit stack 16
.end method
