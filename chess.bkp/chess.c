#include <string.h>
/* #include <conio.h> */

typedef short s16;
typedef long int s32;

void re_turn(void);
void init(void);
void graph(void);
s16 vvod(void);
s16 correct(s16 i0, s16 j0, s16 i1, s16 j1);
void turns(void);
s16 knock(s16 i0, s16 j0);
s16 move(s16 car);
s16 check(void);
void turn_pawn(s16 i, s16 j);
void turn_rook(s16 i0, s16 j0);
void turn_knight(s16 i0, s16 j0);
void turn_bishop(s16 i0, s16 j0);
void turn_queen(s16 i0, s16 j0);
void turn_king(s16 i0, s16 j0);
void mass_load_castle(s16 k, s16 i0);
void mass_load(s16 i, s16 j, s16 i0, s16 j0);
void mass_load_king(s16 i, s16 j, s16 i0, s16 j0);
void mass_load_pass(s16 i, s16 j, s16 i0, s16 j0);
void intel(s16 skill);
s32 power_vs(s32 power, s32 power_0);
s32 estimate(void);
void var_restore(void);
void var_load(void);
void back_move(s16 car);

s32 massiv[2500] = {0};
s16 board[12][12];
s16 knight_i[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
s16 knight_j[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
s16 delta_i[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
s16 delta_j[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
s16 enm, frd, turn, car_base, pass_i, pass_j;
s16 w_king_i, w_king_j, w_castle_short, w_castle_long;
s16 b_king_i, b_king_j, b_castle_short, b_castle_long;

int main(void)
{
	s16 control = 0;
	s16 skill = 0;
	while (1)
	{
		switch (control)
		{
		case 0: // ����� ���
			printf("��᫮ �����뢠���� 室��: ");
			scanf("%d", &skill);
			// cin >> skill;
			init();
			graph();
			turn = 0;
			control = 1;
			enm = 20;
			frd = 10;
			turns();
			break;
		case 1: // ���� �������
			control = vvod();
			break;
		case 2: // ��室 �� �ணࠬ��
			printf("��室 �� �ணࠬ��");
			getchar();
			getchar();
			return 0;
		case 3: // ��।�� �ࠢ�����
			re_turn();
			car_base = 1;
			turns();
			if (car_base == 1)
			{
				if (check())
				{
					printf("��� � ��� !!!");
					turn == 0 ? printf("������ ������.") : printf("������ �����.");
				}
				else
					printf("��� !!! �����");
				control = 0;
				getchar();
				// cin.get();
				printf("\n");
				printf("��� ��筥��� ������");
				// cin.get();
				getchar();
				break;
			}
			control = turn == 0 ? 1 : 4;
			break;
		case 4: // ��� ��⥫����
			intel(skill);
			control = 3;
			break;
		default: // �������⭠� �������
			printf("�������⭠� ������� \n");
			break;
		} // end switch
	} // end while
} // end Main
// ���室 室�
void re_turn(void)
{
	if (turn == 1)
	{
		turn = 0;
		enm = 20;
		frd = 10;
	}
	else
	{
		turn = 1;
		enm = 10;
		frd = 20;
	}
}
void init(void)
{
	s16 i, j;
	w_king_i = 9;
	w_king_j = 6;
	b_king_i = 2;
	b_king_j = 6;
	pass_i = 0;
	w_castle_short = 1;
	w_castle_long = 1;
	b_castle_short = 1;
	b_castle_short = 1;
	car_base = 1;
	massiv[0] = 0;
	// ���������� ᢮����묨 ���⪠��
	for (i = 4; i < 8; i++)
		for (j = 2; j < 10; j++)
			board[i][j] = 1;
	// ���������� ���묨 䨣�ࠬ�
	board[9][2] = board[9][9] = 11; // ����
	board[9][3] = board[9][8] = 12; // ����
	board[9][4] = board[9][7] = 13; // �����
	board[9][5] = 14; // ����
	board[9][6] = 15; // ��஫�
	// ���������� ��묨 䨣�ࠬ�
	board[2][2] = board[2][9] = 21; // ����
	board[2][3] = board[2][8] = 22; // ����
	board[2][4] = board[2][7] = 23; // �����
	board[2][5] = 24; // ����
	board[2][6] = 25; // ��஫�
	// ��誨
	for (j = 2; j < 10; j++)
	{
		board[8][j] = 10; // ����
		board[3][j] = 20; // ����
	}
}
void graph(void)
{
	s16 i, j, k, l, gr_i, gr_j;
	unsigned char gr_board[24][32];
	unsigned char ch;
	// string str_board;
	// clrscr();
	system("cls");
	// ���������� ����᪮�� ���ᨢ�
	for (i = 2; i < 10; i++)
		for (j = 2; j < 10; j++)
		{
		gr_i = (i - 2) * 3;
		gr_j = (j - 2) * 4;
		ch = ((i + j) % 2 == 0) ? (' ') : ('.');
		switch (board[i][j])
		{
		case 1: // ��������� ���⪠
			for (k = gr_i; k < gr_i + 3; k++)
				for (l = gr_j; l < gr_j + 4; l++)
					gr_board[k][l] = ch;
			break;
		case 10:
			gr_board[gr_i][gr_j] = ch;
			gr_board[gr_i][gr_j + 1] = ch;
			gr_board[gr_i][gr_j + 2] = ch;
			gr_board[gr_i][gr_j + 3] = ch;
			gr_board[gr_i + 1][gr_j] = ch;
			gr_board[gr_i + 1][gr_j + 1] = 0xC6;
			gr_board[gr_i + 1][gr_j + 2] = 0xB5;
			gr_board[gr_i + 1][gr_j + 3] = ch;
			gr_board[gr_i + 2][gr_j] = ch;
			gr_board[gr_i + 2][gr_j + 1] = 0xD4;
			gr_board[gr_i + 2][gr_j + 2] = 0xBE;
			gr_board[gr_i + 2][gr_j + 3] = ch;
			break;
		case 11:
			gr_board[gr_i][gr_j] = 0xD5;
			gr_board[gr_i][gr_j + 1] = 0xCB;
			gr_board[gr_i][gr_j + 2] = 0xCB;
			gr_board[gr_i][gr_j + 3] = 0xB8;
			gr_board[gr_i + 1][gr_j] = ch;
			gr_board[gr_i + 1][gr_j + 1] = 0xBA;
			gr_board[gr_i + 1][gr_j + 2] = 0xBA;
			gr_board[gr_i + 1][gr_j + 3] = ch;
			gr_board[gr_i + 2][gr_j] = 0xD4;
			gr_board[gr_i + 2][gr_j + 1] = 0xCA;
			gr_board[gr_i + 2][gr_j + 2] = 0xCA;
			gr_board[gr_i + 2][gr_j + 3] = 0xBE;
			break;
		case 12:
			gr_board[gr_i][gr_j] = 0xD5;
			gr_board[gr_i][gr_j + 1] = 0xD1;
			gr_board[gr_i][gr_j + 2] = 0xCB;
			gr_board[gr_i][gr_j + 3] = 0xB8;
			gr_board[gr_i + 1][gr_j] = 0xD4;
			gr_board[gr_i + 1][gr_j + 1] = 0xCD;
			gr_board[gr_i + 1][gr_j + 2] = 0xB9;
			gr_board[gr_i + 1][gr_j + 3] = ch;
			gr_board[gr_i + 2][gr_j] = 0xD4;
			gr_board[gr_i + 2][gr_j + 1] = 0xCD;
			gr_board[gr_i + 2][gr_j + 2] = 0xCA;
			gr_board[gr_i + 2][gr_j + 3] = 0xBE;
			break;
		case 13:
			gr_board[gr_i][gr_j] = ch;
			gr_board[gr_i][gr_j + 1] = 0xC9;
			gr_board[gr_i][gr_j + 2] = 0xBB;
			gr_board[gr_i][gr_j + 3] = ch;
			gr_board[gr_i + 1][gr_j] = ch;
			gr_board[gr_i + 1][gr_j + 1] = 0xBA;
			gr_board[gr_i + 1][gr_j + 2] = 0xBA;
			gr_board[gr_i + 1][gr_j + 3] = ch;
			gr_board[gr_i + 2][gr_j] = 0xD4;
			gr_board[gr_i + 2][gr_j + 1] = 0xCA;
			gr_board[gr_i + 2][gr_j + 2] = 0xCA;
			gr_board[gr_i + 2][gr_j + 3] = 0xBE;
			break;
		case 14:
			gr_board[gr_i][gr_j] = 0xC7;
			gr_board[gr_i][gr_j + 1] = 0xC1;
			gr_board[gr_i][gr_j + 2] = 0xC1;
			gr_board[gr_i][gr_j + 3] = 0xB6;
			gr_board[gr_i + 1][gr_j] = 0xC8;
			gr_board[gr_i + 1][gr_j + 1] = 0xBB;
			gr_board[gr_i + 1][gr_j + 2] = 0xC9;
			gr_board[gr_i + 1][gr_j + 3] = 0xBC;
			gr_board[gr_i + 2][gr_j] = ch;
			gr_board[gr_i + 2][gr_j + 1] = 0xC8;
			gr_board[gr_i + 2][gr_j + 2] = 0xBC;
			gr_board[gr_i + 2][gr_j + 3] = ch;
			break;
		case 15:
			gr_board[gr_i][gr_j] = 0xC9;
			gr_board[gr_i][gr_j + 1] = 0xD1;
			gr_board[gr_i][gr_j + 2] = 0xD1;
			gr_board[gr_i][gr_j + 3] = 0xBB;
			gr_board[gr_i + 1][gr_j] = 0xC8;
			gr_board[gr_i + 1][gr_j + 1] = 0xBB;
			gr_board[gr_i + 1][gr_j + 2] = 0xC9;
			gr_board[gr_i + 1][gr_j + 3] = 0xBC;
			gr_board[gr_i + 2][gr_j] = ch;
			gr_board[gr_i + 2][gr_j + 1] = 0xC8;
			gr_board[gr_i + 2][gr_j + 2] = 0xBC;
			gr_board[gr_i + 2][gr_j + 3] = ch;
			break;
		case 20:
			gr_board[gr_i][gr_j] = ch;
			gr_board[gr_i][gr_j + 1] = ch;
			gr_board[gr_i][gr_j + 2] = ch;
			gr_board[gr_i][gr_j + 3] = ch;
			gr_board[gr_i + 1][gr_j] = ch;
			gr_board[gr_i + 1][gr_j + 1] = 0xC3;
			gr_board[gr_i + 1][gr_j + 2] = 0xB4;
			gr_board[gr_i + 1][gr_j + 3] = ch;
			gr_board[gr_i + 2][gr_j] = ch;
			gr_board[gr_i + 2][gr_j + 1] = 0xC0;
			gr_board[gr_i + 2][gr_j + 2] = 0xD9;
			gr_board[gr_i + 2][gr_j + 3] = ch;
			break;
		case 21:
			gr_board[gr_i][gr_j] = 0xDA;
			gr_board[gr_i][gr_j + 1] = 0xC2;
			gr_board[gr_i][gr_j + 2] = 0xC2;
			gr_board[gr_i][gr_j + 3] = 0xBF;
			gr_board[gr_i + 1][gr_j] = ch;
			gr_board[gr_i + 1][gr_j + 1] = 0xB3;
			gr_board[gr_i + 1][gr_j + 2] = 0xB3;
			gr_board[gr_i + 1][gr_j + 3] = ch;
			gr_board[gr_i + 2][gr_j] = 0xC0;
			gr_board[gr_i + 2][gr_j + 1] = 0xC1;
			gr_board[gr_i + 2][gr_j + 2] = 0xC1;
			gr_board[gr_i + 2][gr_j + 3] = 0xD9;
			break;
		case 22:
			gr_board[gr_i][gr_j] = 0xDA;
			gr_board[gr_i][gr_j + 1] = 0xC2;
			gr_board[gr_i][gr_j + 2] = 0xC2;
			gr_board[gr_i][gr_j + 3] = 0xBF;
			gr_board[gr_i + 1][gr_j] = 0xC0;
			gr_board[gr_i + 1][gr_j + 1] = 0xC4;
			gr_board[gr_i + 1][gr_j + 2] = 0xB4;
			gr_board[gr_i + 1][gr_j + 3] = ch;
			gr_board[gr_i + 2][gr_j] = 0xC0;
			gr_board[gr_i + 2][gr_j + 1] = 0xC4;
			gr_board[gr_i + 2][gr_j + 2] = 0xC1;
			gr_board[gr_i + 2][gr_j + 3] = 0xD9;
			break;
		case 23:
			gr_board[gr_i][gr_j] = ch;
			gr_board[gr_i][gr_j + 1] = 0xDA;
			gr_board[gr_i][gr_j + 2] = 0xBF;
			gr_board[gr_i][gr_j + 3] = ch;
			gr_board[gr_i + 1][gr_j] = ch;
			gr_board[gr_i + 1][gr_j + 1] = 0xB3;
			gr_board[gr_i + 1][gr_j + 2] = 0xB3;
			gr_board[gr_i + 1][gr_j + 3] = ch;
			gr_board[gr_i + 2][gr_j] = 0xC0;
			gr_board[gr_i + 2][gr_j + 1] = 0xC1;
			gr_board[gr_i + 2][gr_j + 2] = 0xC1;
			gr_board[gr_i + 2][gr_j + 3] = 0xD9;
			break;
		case 24:
			gr_board[gr_i][gr_j] = 0xC3;
			gr_board[gr_i][gr_j + 1] = 0xC1;
			gr_board[gr_i][gr_j + 2] = 0xC1;
			gr_board[gr_i][gr_j + 3] = 0xB4;
			gr_board[gr_i + 1][gr_j] = 0xC0;
			gr_board[gr_i + 1][gr_j + 1] = 0xBF;
			gr_board[gr_i + 1][gr_j + 2] = 0xDA;
			gr_board[gr_i + 1][gr_j + 3] = 0xD9;
			gr_board[gr_i + 2][gr_j] = ch;
			gr_board[gr_i + 2][gr_j + 1] = 0xC0;
			gr_board[gr_i + 2][gr_j + 2] = 0xD9;
			gr_board[gr_i + 2][gr_j + 3] = ch;
			break;
		case 25:
			gr_board[gr_i][gr_j] = 0xDA;
			gr_board[gr_i][gr_j + 1] = 0xC2;
			gr_board[gr_i][gr_j + 2] = 0xC2;
			gr_board[gr_i][gr_j + 3] = 0xBF;
			gr_board[gr_i + 1][gr_j] = 0xC0;
			gr_board[gr_i + 1][gr_j + 1] = 0xBF;
			gr_board[gr_i + 1][gr_j + 2] = 0xDA;
			gr_board[gr_i + 1][gr_j + 3] = 0xD9;
			gr_board[gr_i + 2][gr_j] = ch;
			gr_board[gr_i + 2][gr_j + 1] = 0xC0;
			gr_board[gr_i + 2][gr_j + 2] = 0xD9;
			gr_board[gr_i + 2][gr_j + 3] = ch;
			break;
		default:
			for (k = gr_i; k < gr_i + 3; k++)
				for (l = gr_j; l < gr_j + 4; l++)
					gr_board[k][l] = 'X';
			break;
		} // end switch
	} // end for j
	// ���ᮢ�� 誠��
	for (i = 22, ch = '1'; i > 0; ch++, i -= 3)
		gr_board[i][0] = ch;
	for (j = 2, ch = 'A'; j < 32; ch++, j += 4)
		gr_board[23][j] = ch;
	// �뢮� ����᪮�� ���ᨢ�
	for (i = 0; i < 24; i++)
	{
		for (j = 0; j < 32; j++)
			// cout << gr_board[i][j];
               printf("%c", gr_board[i][j]);
		// str_board += '\n';
		printf("\n");
	}
	// cout << str_board;
} // end graph(void)
// ����
s16 vvod(void)
{
	// string str;
	char str[80];
	s16 err;
	// �஢�ઠ ���४⭮�� �����
	while (1)
	{
		err = 0;
		printf("����: ");
		scanf("%s", str);
		switch (strlen(str))
		{
		case 0: // ���� ���⮩ ��ப�
			err = 1;
			break;
		case 1: // ���� �������
			switch (str[0])
			{
			case 'n': // ����� ���
				return 0;
			case 'm': // ���ᨢ 室��
				for (s16 t = 0; t < car_base; t++)
					printf("%d ", massiv[t]);
				continue;
			case 'r': // ����ᮢ�� �࠭�
				graph();
				continue;
			case 'x': // ��室 �� �ணࠬ��
				return 2;
			default: // ���� �������⥭
				err = 1;
				break;
			} // end switch
			break;
		case 4: // ���� ��६�饭��
			err = 1;
			if (str[0] < 'a' || str[0] > 'h') break;
			if (str[1] < '1' || str[1] > '8') break;
			if (str[2] < 'a' || str[2] > 'h') break;
			if (str[3] < '1' || str[3] > '8') break;
			{
				s16 i0 = 10 - (str[1] - '1' + 1);
				s16 j0 = str[0] - 'a' + 2;
				s16 i1 = 10 - (str[3] - '1' + 1);
				s16 j1 = str[2] - 'a' + 2;
				s16 car;
				// ��६�饭��
				car = correct(i0, j0, i1, j1);
				if (car != 0)
				{
					move(car);
					graph();
					return 3;
				}
			}
			break;
		default: // ���� �������⥭
			err = 1;
			break;
		} // end switch
		if (err)
		{
			printf("�������⭠� �������. \n");
			continue;
		}
		break;
	}
	return 2;
}
// �஢�ઠ ���४⭮��
s16 correct(s16 i0, s16 j0, s16 i1, s16 j1)
{
	s16 car = 0;
	while (1)
	{
		// ���� �㫥���� ���祭��
		for (; massiv[car] != 0; car += 3)
		{}
		car++;
		// �᫮��� ��室�
		if (car == car_base)
			return 0;
		if (i0 != massiv[car + 1]) continue;
		if (j0 != massiv[car + 2]) continue;
		if (i1 != massiv[car + 4]) continue;
		if (j1 != massiv[car + 5]) continue;
		return car;
	}
}
// �����⨬� 室�
void turns(void)
{
	// ��ॡ�ࠥ� ���� ���ᨢ �� ���⪠�
	s16 i, j, a0;
	for (i = 2; i < 10; i++)
	{
		for (j = 2; j < 10; j++)
		{
			a0 = board[i][j];
			// �᫨ �� ᢮� 䨣��, � ᫥����� ���⪠
			if (a0 < frd || a0 > frd + 5)
				continue;
			switch (a0)
			{
			case 10: // ��誠
			case 20:
				turn_pawn(i, j);
				break;
			case 11: //�����
			case 21:
				turn_rook(i, j);
				break;
			case 12:// ����
			case 22:
				turn_knight(i, j);
				break;
			case 13: // ����
			case 23:
				turn_bishop(i, j);
				break;
			case 14: // ����
			case 24:
				turn_queen(i, j);
				break;
			case 15: // ��஫�
			case 25:
				turn_king(i, j);
				break;
			}
		}
	} // end for
} // end turns()
// ��।������ ��室���� �� ���⪠ ��� 㤠஬
s16 knock(s16 i0, s16 j0)
{
	s16 knight = enm + 2; // 12 ��� 22
	s16 n;
	// ���� �����
	for (n = 0; n < 8; n++)
	if (board[(i0 + knight_i[n])][(j0 + knight_j[n])] == knight)
		return 1;
	// ���� ��㣮� 䨣�ன
	s16 i, j;
	s16 queen = enm + 4; // 14 ��� 24
	s16 king = enm + 5; // 15 ��� 25
	s16 bishop_rook, di, dj, a0;
	s16 first;
	for (n = 0; n < 8; n++)
	{
		i = i0;
		j = j0;
		first = 1;
		if (n % 2 == 0)
			bishop_rook = enm + 1;
		else
			bishop_rook = enm + 3;
		di = delta_i[n];
		dj = delta_j[n];
		while (1)
		{
			i += di;
			j += dj;
			a0 = board[i][j];
			// �᫨ ᢮������ ���⪠, � ���室 � ᫥���饩
			if (a0 == 1)
			{
				first = 0;
				continue;
			}
			// �᫨ �࠭��, � ��室
			if (a0 == 0)
				break;
			// �᫨ �ᥤ��� ���⪠
			if (first)
			{
				// �஢�ਬ, ��� �� ��஫�
				if (a0 == king)
					return 1;
				// �஢�ਬ, ��� �� ��誨
				if (turn == 0)
				{
					if (n == 1 || n == 7)
						if (a0 == enm)
							return 1;
				}
				else
				{
					if (n == 3 || n == 5)
						if (a0 == enm)
							return 1;
				}
			} // end if
			if (a0 == queen || a0 == bishop_rook)
				return 1;
			break;
		} // end while
	} // end for
	return 0;
}
s16 move(s16 car)
{
	s16 knock_check = 0;
	s16 i0, j0, i1, j1, a0, a1;
	pass_i = 0;
	if (car_base <= 2000)
		if (check())
			knock_check = 1;
	while (1)
	{
		// �᫨ ���⨥ �� ��室�
		if (massiv[car + 3] == 0)
		{
			i0 = massiv[car + 1];
			j0 = massiv[car + 2];
			board[i0][j0] = 1;
			// ��� 㤠��
			knock_check = 1;
			break;
		}
		// ��।��� ���न����
		a0 = massiv[car];
		i0 = massiv[car + 1];
		j0 = massiv[car + 2];
		a1 = massiv[car + 3];
		i1 = massiv[car + 4];
		j1 = massiv[car + 5];
		// ��� 㤠��
		if (a1 != 1)
			knock_check = 1;
		// ��誠 �⠭������ �৥�
		if (a0 == frd)
		{
			if (i1 == 2) a0 = 14;
			else
			if (i1 == 9) a0 = 24;
		}
		// ��६�頥�
		if (a0 == 15) // �᫨ ���� ��஫�
		{
			w_king_i = i1;
			w_king_j = j1;
			w_castle_short = 0;
			w_castle_long = 0;
		}
		else if (a0 == 25) // �᫨ ��� ��஫�
		{
			b_king_i = i1;
			b_king_j = j1;
			b_castle_short = 0;
			b_castle_long = 0;
		}
		else if (a0 == 11) // �᫨ ����� �����
		{
			if (w_castle_long == 1)
			{
				if (i0 == 9 && j0 == 2)
					w_castle_long = 0;
			}
			if (w_castle_short == 1)
			{
				if (i0 == 9 && j0 == 9)
					w_castle_short = 0;
			}
		}
		else if (a0 == 21) // �᫨ �ୠ� �����
		{
			if (b_castle_long == 1)
			{
				if (i0 == 2 && j0 == 2)
					b_castle_long = 0;
			}
			if (b_castle_short == 1)
			{
				if (i0 == 2 && j0 == 9)
					b_castle_short = 0;
			}
		}
		// �� ���⨨ ����
		else if (a1 == 11) // �᫨ ����� �����
		{
			if (w_castle_long == 1)
			{
				if (i1 == 9 && j1 == 2)
					w_castle_long = 0;
			}
			if (w_castle_short == 1)
			{
				if (i1 == 9 && j1 == 9)
					w_castle_short = 0;
			}
		}
		else if (a1 == 21) // �᫨ �ୠ� �����
		{
			if (b_castle_long == 1)
			{
				if (i1 == 2 && j1 == 2)
					b_castle_long = 0;
			}
			if (b_castle_short == 1)
			{
				if (i1 == 2 && j1 == 9)
					b_castle_short = 0;
			}
		}
		board[i0][j0] = 1;
		board[i1][j1] = a0;
		// �᫨ ����� �����, � ��室
		if (massiv[car += 6] == 0)
		{
			// ��॥��塞 ����������� ����� �� ��室�
			if (a0 == 10)
			{
				if (i0 != 8) break;
				if (i1 != 6) break;
				if (board[i1][j1 - 1] == 20 || board[i1][j1 + 1] == 20)
				{
					pass_i = i1;
					pass_j = j1;
				}
			}
			else if (a0 == 20)
			{
				if (i0 != 3) break;
				if (i1 != 5) break;
				if (board[i1][j1 - 1] == 10 || board[i1][j1 + 1] == 10)
				{
					pass_i = i1;
					pass_j = j1;
				}
			}
			break;
		} // end if
	} // end while
	if (car_base > 2000)
		return 2;
	// �ࠦ�᪨� ��஫� ��� �宬
	if (knock_check != 1)
	{
		re_turn();
		if (check())
			knock_check = 1;
		re_turn();
	}
	return knock_check;
}
// �஢�ઠ �� ��
s16 check(void) // was bool
{
	return turn == 0 ? knock(w_king_i, w_king_j) : knock(b_king_i, b_king_j);
}
// ��� ��誮�
void turn_pawn(s16 i, s16 j)
{
	s16 dir_kn_1, dir_kn_2, dir_m, i_beg, a0, i0, j0;
	if (turn == 0)
	{
		dir_kn_1 = 7;
		dir_kn_2 = 1;
		dir_m = 0;
		i_beg = 8;
	}
	else
	{
		dir_kn_1 = 5;
		dir_kn_2 = 3;
		dir_m = 4;
		i_beg = 3;
	}
	// ��ࢮ� ���ࠢ����� 㤠�
	i0 = i + delta_i[dir_kn_1];
	j0 = j + delta_j[dir_kn_1];
	a0 = board[i0][j0];
	if (a0 >= enm && a0 <= enm + 5)
		mass_load(i, j, i0, j0);
	// ���⨥ �� ��室�
	if (i == pass_i)
	{
		if (pass_j == j - 1)
			mass_load_pass(i, j, i0, j0);
	}
	// ��஥ ���ࠢ����� 㤠�
	i0 = i + delta_i[dir_kn_2];
	j0 = j + delta_j[dir_kn_2];
	a0 = board[i0][j0];
	if (a0 >= enm && a0 <= enm + 5)
		mass_load(i, j, i0, j0);
	// ���⨥ �� ��室�
	if (i == pass_i)
	{
		if (pass_j == j + 1)
			mass_load_pass(i, j, i0, j0);
	}
	// ��� �� 1 �����
	i0 = i + delta_i[dir_m];
	j0 = j + delta_j[dir_m];
	a0 = board[i0][j0];
	if (a0 == 1)
	{
		mass_load(i, j, i0, j0);
		// ��� �� 2 ���⪨
		if (i == i_beg)
		{
			i0 += delta_i[dir_m];
			j0 += delta_j[dir_m];
			a0 = board[i0][j0];
			if (a0 == 1)
				mass_load(i, j, i0, j0);
		}
	}
} // end turn_pawn
// ��� ���쥩
void turn_rook(s16 i0, s16 j0)
{
	s16 n, di, dj, i, j, a0;
	for (n = 0; n < 8; n += 2)
	{
		i = i0;
		j = j0;
		di = delta_i[n];
		dj = delta_j[n];
		while (1)
		{
			i += di;
			j += dj;
			a0 = board[i][j];
			// �᫮��� ��室�
			if (a0 == 0)
				break;
			if (a0 >= frd && a0 <= frd + 5)
				break;
			mass_load(i0, j0, i, j);
			if (a0 != 1)
				break;
		}
	}
} // end turn_rook
// ��� �����
void turn_knight(s16 i0, s16 j0)
{
	s16 n, i, j, a0;
	for (n = 0; n < 8; n++)
	{
		i = i0 + knight_i[n];
		j = j0 + knight_j[n];
		a0 = board[i][j];
		// �᫮��� ��室�
		if (a0 == 0)
			continue;
		if (a0 >= frd && a0 <= frd + 5)
			continue;
		mass_load(i0, j0, i, j);
	}
}
// ��� ᫮���
void turn_bishop(s16 i0, s16 j0)
{
	s16 n, i, j, di, dj, a0;
	for (n = 1; n < 8; n += 2)
	{
		i = i0;
		j = j0;
		di = delta_i[n];
		dj = delta_j[n];
		while (1)
		{
			i += di;
			j += dj;
			a0 = board[i][j];
			// �᫮��� ��室�
			if (a0 == 0)
				break;
			if (a0 >= frd && a0 <= frd + 5)
				break;
			mass_load(i0, j0, i, j);
			if (a0 != 1)
				break;
		}
	}
}
// ��� �৥�
void turn_queen(s16 i0, s16 j0)
{
	s16 n, i, j, di, dj, a0;
	for (n = 0; n < 8; n++)
	{
		i = i0;
		j = j0;
		di = delta_i[n];
		dj = delta_j[n];
		while (1)
		{
			i += di;
			j += dj;
			a0 = board[i][j];
			// �᫮��� ��室�
			if (a0 == 0)
				break;
			if (a0 >= frd && a0 <= frd + 5)
				break;
			mass_load(i0, j0, i, j);
			if (a0 != 1)
				break;
		}
	}
} // end turn_queen
// ��� ��஫��
void turn_king(s16 i0, s16 j0)
{
	s16 n, i, j, a0;
	for (n = 0; n < 8; n++)
	{
		i = i0 + delta_i[n];
		j = j0 + delta_j[n];
		a0 = board[i][j];
		// �᫮��� ��室�
		if (a0 == 0)
			continue;
		if (a0 >= frd && a0 <= frd + 5)
			continue;
		mass_load_king(i0, j0, i, j);
		if (turn == 0)
		{
			if (w_castle_long == 1)
				mass_load_castle(-1, 9);
			if (w_castle_short == 1)
				mass_load_castle(1, 9);
		}
		else
		{
			if (b_castle_long == 1)
				mass_load_castle(-1, 2);
			if (b_castle_short == 1)
				mass_load_castle(1, 2);
		}
	}
} // end turn_king
// ����㧪� � ���ᨢ 室�� ��� ப�஢��
void mass_load_castle(s16 k, s16 i0)
{
	// ���न����
	const s16 j0 = 6;
	s16 j, j_max, j_rook;
	j_max = j0 + (k * 3);
	if (k == -1)
		j_rook = 2;
	else
		j_rook = 9;
	// �஢�ਬ ᢮����� ���⪨
	for (j = j0 + k; j != j_rook; j += k)
		if (board[i0][j] != 1)
			return;
	// �஢�ਬ "㤠��" ���⪨
	for (j = j0; j != j_max; j += k)
		if (knock(i0, j))
			return;
	// �����㥬�� ��஫��
	massiv[car_base++] = board[i0][j0];
	massiv[car_base++] = i0;
	massiv[car_base++] = j0;
	massiv[car_base++] = 1;
	massiv[car_base++] = i0;
	massiv[car_base++] = (j -= k);
	// �����㥬�� ���쥩
	massiv[car_base++] = board[i0][j_rook];
	massiv[car_base++] = i0;
	massiv[car_base++] = j_rook;
	massiv[car_base++] = 1;
	massiv[car_base++] = i0;
	massiv[car_base++] = j - k;
	massiv[car_base++] = 0;
}
// ����㧪� � ���ᨢ 室��
void mass_load(s16 i, s16 j, s16 i0, s16 j0)
{
	s16 a = board[i][j];
	s16 a0 = board[i0][j0];
	// �ந������ ��������� �� ��᪥
	board[i][j] = 1;
	board[i0][j0] = a;
	// �஢��塞 �� ��
	if (!check())
	{
		massiv[car_base++] = a;
		massiv[car_base++] = i;
		massiv[car_base++] = j;
		massiv[car_base++] = a0;
		massiv[car_base++] = i0;
		massiv[car_base++] = j0;
		massiv[car_base++] = 0;
	}
	// �⬥�塞 ���������
	board[i][j] = a;
	board[i0][j0] = a0;
}
// ����㧪� � ���ᨢ 室�� ��� ��஫�
void mass_load_king(s16 i, s16 j, s16 i0, s16 j0)
{
	s16 baking_i = 0, baking_j = 0;
	s16 a = board[i][j];
	s16 a0 = board[i0][j0];
	if (a == 15)
	{
		baking_i = w_king_i;
		baking_j = w_king_j;
		w_king_i = i0;
		w_king_j = j0;
	}
	else if (a == 25)
	{
		baking_i = b_king_i;
		baking_j = b_king_j;
		b_king_i = i0;
		b_king_j = j0;
	}
	// �ந������ ��������� �� ��᪥
	board[i][j] = 1;
	board[i0][j0] = a;
	// �஢��塞 �� ��
	if (!check())
	{
		massiv[car_base++] = a;
		massiv[car_base++] = i;
		massiv[car_base++] = j;
		massiv[car_base++] = a0;
		massiv[car_base++] = i0;
		massiv[car_base++] = j0;
		massiv[car_base++] = 0;
	}
	// �⬥�塞 ���������
	board[i][j] = a;
	board[i0][j0] = a0;
	if (a == 15)
	{
		w_king_i = baking_i;
		w_king_j = baking_j;
	}
	else if (a == 25)
	{
		b_king_i = baking_i;
		b_king_j = baking_j;
	}
}
// ����㧪� � ���ᨢ 室�� ��� ����� �� ��室�
void mass_load_pass(s16 i, s16 j, s16 i0, s16 j0)
{
	s16 a = board[i][j];
	s16 a0 = board[i0][j0];
	s16 b = board[pass_i][pass_j];
	// �ந������ ��������� �� ��᪥
	board[i][j] = 1;
	board[i0][j0] = a;
	board[pass_i][pass_j] = 1;
	// �஢��塞 �� ��
	if (!check())
	{
		massiv[car_base++] = a;
		massiv[car_base++] = i;
		massiv[car_base++] = j;
		massiv[car_base++] = a0;
		massiv[car_base++] = i0;
		massiv[car_base++] = j0;
		massiv[car_base++] = b;
		massiv[car_base++] = pass_i;
		massiv[car_base++] = pass_j;
		massiv[car_base++] = 0;
	}
	// �⬥�塞 ���������
	board[i][j] = a;
	board[i0][j0] = a0;
	board[pass_i][pass_j] = b;
}
/* ��⥫���� */
	void intel(s16 skill)
	{
		s16 depth = 0, alt_depth = 0, xz = 0;
		s32 tabl[600] = {0};
		// ���������� ⠡���� 室��
		s16 car_tab = 0, car = 0, car_fix, car_max;
		s32 bad = 0, neutral = 0, good = 0;
		s32 power, power_0 = 0, power_base = estimate();
		while (1)
		{
			// �᫮��� ��室� (����� ⠡����, ����� ����� � ���ᨢ� 室��)
			if (car_tab > 599)
			{
				printf("��室 �� �࠭��� ���ᨢ� tabl[] !!! \n");
				getchar();
				getchar();
				break;
			}
			// ���� �㫥���� ���祭��
			for (; massiv[car] != 0; car += 3)
			{}
			car++;
			// �᫮��� ��室�
			if (car == car_base) break;
			// ������塞 ⠡����
			tabl[car_tab] = car;
			car_tab += 6;
		} // end while
		car_max = car_tab - 6;
	forward:
		// ��६ 室 � ������
		if (depth == 0)
		{
			// �᫮��� �४�饭�� �����
			if (car_tab == 0)
				goto end_intel;
			car_tab -= 6;
			massiv[car_base++] = alt_depth;
			var_load();
			car = tabl[car_tab];
			depth++;
			xz = move(car);
			if (xz == 0)
				alt_depth += depth;
			else if (xz == 2)
				alt_depth = skill;
			else
				alt_depth += (depth / 2);
			bad = 0;
			neutral = 0;
			good = 0;
			power_0 = 100;
		}
		else
		{
			// ���� ��� � ���⭮� ���ࠢ�����
			for (car = car_base - 2; massiv[car] != 0; car -= 3)
			{}
			car++;
			massiv[car_base++] = alt_depth;
			var_load();
			depth++;
			xz = move(car);
			if (xz == 0)
				alt_depth += depth;
			else if (xz == 2)
				alt_depth = skill;
			else
				alt_depth += (depth / 2);
		}
		// �஢�ઠ ���⨦���� ��㡨�� �����
		if (alt_depth >= skill)
		{
			// �業��
			power = estimate();
			if (power > power_base)
				good++;
			else if (power < power_base)
				bad++;
			else
				neutral++;
			power_0 = power_vs(power, power_0);
			goto back;
		} // end if
		// ��।�� 室� �����
		massiv[car_base++] = power_0;
		massiv[car_base++] = 100;
		massiv[car_base++] = 0;
		// �஢�ਬ ����������� ���쭥�襩 ����
		re_turn();
		car_fix = car_base;
		turns();
		if (car_fix == car_base)
		{
			if (check())
			{
				if (turn == 0)
				{
					power_0 = 50;
					good++;
				}
				else
				{
					power_0 = -50;
					bad++;
				}
			}
			else
			{
				if (power_base < 0)
				{
					good++;
					power_0 = 50;
				}
				else if (power_base > 0)
				{
					bad++;
					power_0 = -50;
				}
				else
				{
					neutral++;
					power_0 = 0;
				}
			}
			goto back_turn;
		} // end if
		power_0 = 100;
		goto forward;
		// ��।�� 室� �����
	back_turn:
		re_turn();
		car_base -= 3;
		power = power_0;
		power_0 = massiv[car_base];
		power_0 = power_vs(power, power_0);
		//�⪠� �����
	back:
		if (depth == 1) // �஢��� ��ࢮ�� 室�
		{
			car = tabl[car_tab];
			var_restore();
			alt_depth = massiv[--car_base];
			back_move(car);
			tabl[car_tab + 1] = power_0;
			tabl[car_tab + 2] = bad;
			tabl[car_tab + 3] = neutral;
			tabl[car_tab + 4] = good;
			depth--;
			goto forward;
		}
		else // �஢��� ��᫥����� 室��
		{
			var_restore();
			alt_depth = massiv[--car_base];
			// ���� ��� � ���⭮� ���ࠢ�����
			for (car_base -= 2; massiv[car_base] != 0; car_base -= 3)
			{}
			car_base++;
			back_move(car_base);
			depth--;
			// �஢�ਬ, ���� �� ��� 室� � ������ ����樨
			if (massiv[car_base - 2] == 100)
				goto back_turn;
			goto forward;
		}
		// ����� �����
	end_intel:
		// �롮� 室� - ��।������ ���ᨬ��쭮� �業��
		power = -100;
		for (car_tab = 0; car_tab <= car_max; car_tab += 6)
		{
			if (tabl[car_tab + 1] > power)
				power = tabl[car_tab + 1];
		}
		// ����塞 ����⨪� ��� ���ᨬ��쭮� �業��
		if (power >= power_base)
		{
			for (car_tab = 0; car_tab <= car_max; car_tab += 6)
			{
				if (tabl[car_tab + 1] == power)
					tabl[car_tab + 5] = (100 * tabl[car_tab + 4]) / (tabl[car_tab + 2] + tabl[car_tab + 3] + tabl[car_tab + 4]);
			}
		}
		else
		{
			for (car_tab = 0; car_tab <= car_max; car_tab += 6)
			{
				if (tabl[car_tab + 1] == power)
					tabl[car_tab + 5] = (100 * tabl[car_tab + 2]) / (tabl[car_tab + 2] + tabl[car_tab + 3] + tabl[car_tab + 4]);
			}
		}
		// ��।��塞 �������� ����⨪�
		if (power >= power_base)
		{
			power_0 = 0;
			for (car_tab = 0; car_tab <= car_max; car_tab += 6)
			{
				if (tabl[car_tab + 1] == power && tabl[car_tab + 5] > power_0)
					power_0 = tabl[car_tab + 5];
			}
		}
		else
		{
			power_0 = 100;
			for (car_tab = 0; car_tab <= car_max; car_tab += 6)
			{
				if (tabl[car_tab + 1] == power && tabl[car_tab + 5] < power_0)
					power_0 = tabl[car_tab + 5];
			}
		}
		// ������ �������� �������� 室
		for (car_tab = 0; car_tab <= car_max; car_tab += 6)
		{
			if (tabl[car_tab + 1] == power && tabl[car_tab + 5] == power_0)
			{
				move(tabl[car_tab]);
				printf("power = %d, power_0 = %d", power, power_0);
				getchar();
				getchar();
				break;
			}
		}
		graph();
	} // end intel
// �ࠢ����� �業��
s32 power_vs(s32 power, s32 power_0)
{
	/*
	if (power_0 == 100)
		return power;
	if (turn == 0)
	{
		if (power_0 > power)
			return power;
		else
			return power_0;
	}
	else
	{
		if (power_0 > power)
			return power_0;
		else
			return power;
	}  */
	/* Optimized code */
	if (power_0 == 100)
		return power;
	if (turn == 0)
	{
		return power_0 > power ? power : power_0;
	}
	return power_0 > power ? power_0 : power;
}
s32 estimate(void)
{
	s32 power = 0;
	s16 i, j, a;
	for (i = 2; i < 10; i++)
	{
		for (j = 2; j < 10; j++)
		{
			a = board[i][j];
			if (a == 1)
				continue;
			if (a < 20)
			{
				switch (a)
				{
				case 10:
					power--;
					break;
				case 11:
					power -= 5;
					break;
				case 12:
					power -= 3;
					break;
				case 13:
					power -= 3;
					break;
				case 14:
					power -= 9;
					break;
				} // end switch
			}
			else
			{
				switch (a)
				{
				case 20:
					power++;
					break;
				case 21:
					power += 5;
					break;
				case 22:
					power += 3;
					break;
				case 23:
					power += 3;
					break;
				case 24:
					power += 9;
					break;
				} // end switch
			}
		} // end for
	} // end for
	return power;
}
void var_restore(void)
{
	// ����⠭�������� ��६����
	car_base--;
	b_castle_long = massiv[car_base--];
	b_castle_short = massiv[car_base--];
	w_castle_long = massiv[car_base--];
	w_castle_short = massiv[car_base--];
	pass_j = massiv[car_base--];
	pass_i = massiv[car_base--];
	b_king_j = massiv[car_base--];
	b_king_i = massiv[car_base--];
	w_king_j = massiv[car_base--];
	w_king_i = massiv[car_base];
}
void var_load(void)
{
	// ����㦠�� ��६����
	massiv[car_base++] = w_king_i;
	massiv[car_base++] = w_king_j;
	massiv[car_base++] = b_king_i;
	massiv[car_base++] = b_king_j;
	massiv[car_base++] = pass_i;
	massiv[car_base++] = pass_j;
	massiv[car_base++] = w_castle_short;
	massiv[car_base++] = w_castle_long;
	massiv[car_base++] = b_castle_short;
	massiv[car_base++] = b_castle_long;
}
// �⪠� �����
void back_move(s16 car)
{
	// �⬥�� ��������� �� ��᪥
	s16 i, j, a;
	do
	{
		a = massiv[car++];
		i = massiv[car++];
		j = massiv[car++];
		board[i][j] = a;
	} while (massiv[car] != 0);
}
