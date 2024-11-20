/*
 * @Author: your name
 * @Date: 2021-07-08 10:04:08
 * @LastEditTime: 2021-07-21 13:34:18
 * @LastEditors: Please set LastEditors
 * @Description: LCD��ʾ����ʼ��
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Drivers\BSP\BSP_LCD.c
 */
#include "BSP_LCD.h"
#include "font.h"
#include "OS_Delay.h"
#include "OS_Debug.h"
#include "cmsis_os.h"

static uint16_t POINT_COLOR = DARKBLUE; //������ɫ
static uint16_t BACK_COLOR = WHITE;     //����ɫ

//����LCD��Ҫ����: Ĭ��Ϊ����
_lcd_dev g_lcddev;

/**
 * @description: д�Ĵ�������
 * @param {uint16_t} regval �Ĵ���ֵ
 * @return {*}
 */
void LCD_WR_REG(uint16_t regval)
{
    volatile int i = 0;
    regval = regval;       //ʹ��-O2�Ż���ʱ��,����������ʱ
    LCD->LCD_REG = regval; //д��Ҫд�ļĴ������
}

/**
 * @description: дLCD����
 * @param {uint16_t} data Ҫд���ֵ
 * @return {*}
 */
void LCD_WR_DATA(uint16_t data)
{
    volatile int i = 0;
    data = data; //ʹ��-O2�Ż���ʱ��,����������ʱ
    LCD->LCD_RAM = data;
}

/**
 * @description: ��LCD����
 * @param {*}
 * @return {*} ������ֵ
 */
uint16_t LCD_RD_DATA(void)
{
    uint16_t ram; //��ֹ���Ż�
    ram = LCD->LCD_RAM;
    return ram;
}

/**
 * @description: д�Ĵ���
 * @param {uint16_t} LCD_Reg �Ĵ�����ַ
 * @param {uint16_t} LCD_RegValue Ҫд�������
 * @return {*}
 */
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
    LCD->LCD_REG = LCD_Reg;      //д��Ҫд�ļĴ������
    LCD->LCD_RAM = LCD_RegValue; //д������
}

/**
 * @description: ���Ĵ���
 * @param {uint16_t} LCD_Reg�Ĵ�����ַ
 * @return {*}����������
 */
uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
    LCD_WR_REG(LCD_Reg); //д��Ҫ���ļĴ������
    delay_us(5);
    return LCD_RD_DATA(); //���ض�����ֵ
}

/**
 * @description: ��ʼдGRAM
 * @param {*}
 * @return {*}
 */
void LCD_WriteRAM_Prepare(void)
{
    LCD->LCD_REG = g_lcddev.wramcmd;
}

/**
 * @description: LCDдGRAM
 * @param {uint16_t} RGB_Code��ɫֵ
 * @return {*}
 */
void LCD_WriteRAM(uint16_t RGB_Code)
{
    LCD->LCD_RAM = RGB_Code; //дʮ��λGRAM
}

/**
 * @description: ͨ���ú���ת�� ��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
 * @param {uint16_t} c GBR��ʽ����ɫֵ
 * @return {*} ����ֵ��RGB��ʽ����ɫֵ
 */
uint16_t LCD_BGR2RGB(uint16_t c)
{
    uint16_t r, g, b, rgb;
    b = (c >> 0) & 0x1f;
    g = (c >> 5) & 0x3f;
    r = (c >> 11) & 0x1f;
    rgb = (b << 11) + (g << 5) + (r << 0);
    return (rgb);
}

/**
 * @description: ��mdk -O1ʱ���Ż�ʱ��Ҫ����
 * @param {uint8_t} i ��ʱi
 * @return {*}
 */
void opt_delay(uint8_t i)
{
    while (i--)
        ;
}

/**
 * @description: ��ȡ��ĳ�����ɫֵ
 * @param {uint16_t} x ����
 * @param {uint16_t} y ����
 * @return {*} �˵����ɫ
 */
uint16_t LCD_ReadPoint(uint16_t x, uint16_t y)
{
    uint16_t r = 0, g = 0, b = 0;
    if (x >= g_lcddev.width || y >= g_lcddev.height)
        return 0; //�����˷�Χ,ֱ�ӷ���
    LCD_SetCursor(x, y);
    if (g_lcddev.id == 0X5510)
        LCD_WR_REG(0X2E00); //5510 ���Ͷ�GRAMָ��
    r = LCD_RD_DATA();      //dummy Read
    opt_delay(2);
    r = LCD_RD_DATA();         //ʵ��������ɫ
    if (g_lcddev.id == 0X5510) //9341/NT35310/NT35510Ҫ��2�ζ���
    {
        opt_delay(2);
        b = LCD_RD_DATA();
        g = r & 0XFF; //����9341/5310/5510,��һ�ζ�ȡ����RG��ֵ,R��ǰ,G�ں�,��ռ8λ
        g <<= 8;
    }
    if (g_lcddev.id == 0X5510)
        return (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11)); //ILI9341/NT35310/NT35510��Ҫ��ʽת��һ��

    return 0;
}

/**
 * @description: LCD������ʾ
 * @param {*}
 * @return {*}
 */
void LCD_DisplayOn(void)
{
    if (g_lcddev.id == 0X5510)
        LCD_WR_REG(0X2900); //������ʾ
}

/**
 * @description: LCD�ر���ʾ
 * @param {*}
 * @return {*}
 */
void LCD_DisplayOff(void)
{
    if (g_lcddev.id == 0X5510)
        LCD_WR_REG(0X2800); //�ر���ʾ
}

/**
 * @description: ���ù��λ��
 * @param {uint16_t} Xpos ������
 * @param {uint16_t} Ypos ������
 * @return {*}
 */
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    LCD_WR_REG(g_lcddev.setxcmd);
    LCD_WR_DATA(Xpos >> 8);
    LCD_WR_REG(g_lcddev.setxcmd + 1);
    LCD_WR_DATA(Xpos & 0XFF);
    LCD_WR_REG(g_lcddev.setycmd);
    LCD_WR_DATA(Ypos >> 8);
    LCD_WR_REG(g_lcddev.setycmd + 1);
    LCD_WR_DATA(Ypos & 0XFF);
}

/**
 * @description: ����LCD���Զ�ɨ�跽��(һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.)
 * @param {uint8_t} dir 0~7,����8������(���嶨���lcd.h)
 * @return {*}
 */
void LCD_Scan_Dir(uint8_t dir)
{
    uint16_t regval = 0;
    uint16_t dirreg = 0;
    uint16_t temp;
    if (g_lcddev.id == 0X5510)
    {
        switch (dir)
        {
        case L2R_U2D: //������,���ϵ���
            regval |= (0 << 7) | (0 << 6) | (0 << 5);
            break;
        case L2R_D2U: //������,���µ���
            regval |= (1 << 7) | (0 << 6) | (0 << 5);
            break;
        case R2L_U2D: //���ҵ���,���ϵ���
            regval |= (0 << 7) | (1 << 6) | (0 << 5);
            break;
        case R2L_D2U: //���ҵ���,���µ���
            regval |= (1 << 7) | (1 << 6) | (0 << 5);
            break;
        case U2D_L2R: //���ϵ���,������
            regval |= (0 << 7) | (0 << 6) | (1 << 5);
            break;
        case U2D_R2L: //���ϵ���,���ҵ���
            regval |= (0 << 7) | (1 << 6) | (1 << 5);
            break;
        case D2U_L2R: //���µ���,������
            regval |= (1 << 7) | (0 << 6) | (1 << 5);
            break;
        case D2U_R2L: //���µ���,���ҵ���
            regval |= (1 << 7) | (1 << 6) | (1 << 5);
            break;
        }
        if (g_lcddev.id == 0X5510)
            dirreg = 0X3600;
        LCD_WriteReg(dirreg, regval);

        if (regval & 0X20)
        {
            if (g_lcddev.width < g_lcddev.height) //����X,Y
            {
                temp = g_lcddev.width;
                g_lcddev.width = g_lcddev.height;
                g_lcddev.height = temp;
            }
        }
        else
        {
            if (g_lcddev.width > g_lcddev.height) //����X,Y
            {
                temp = g_lcddev.width;
                g_lcddev.width = g_lcddev.height;
                g_lcddev.height = temp;
            }
        }

        LCD_WR_REG(g_lcddev.setxcmd);
        LCD_WR_DATA(0);
        LCD_WR_REG(g_lcddev.setxcmd + 1);
        LCD_WR_DATA(0);
        LCD_WR_REG(g_lcddev.setxcmd + 2);
        LCD_WR_DATA((g_lcddev.width - 1) >> 8);
        LCD_WR_REG(g_lcddev.setxcmd + 3);
        LCD_WR_DATA((g_lcddev.width - 1) & 0XFF);
        LCD_WR_REG(g_lcddev.setycmd);
        LCD_WR_DATA(0);
        LCD_WR_REG(g_lcddev.setycmd + 1);
        LCD_WR_DATA(0);
        LCD_WR_REG(g_lcddev.setycmd + 2);
        LCD_WR_DATA((g_lcddev.height - 1) >> 8);
        LCD_WR_REG(g_lcddev.setycmd + 3);
        LCD_WR_DATA((g_lcddev.height - 1) & 0XFF);
    }
}

/**
 * @description: ����
 * @param {uint16_t} x ����
 * @param {uint16_t} y
 * @return {*} 
 */
void LCD_DrawPoint(uint16_t x, uint16_t y)
{
    LCD_SetCursor(x, y);        //���ù��λ��
    LCD_WriteRAM_Prepare();     //��ʼд��GRAM
    LCD->LCD_RAM = POINT_COLOR; //�˵����ɫ
}

/**
 * @description: ���ٻ���
 * @param {uint16_t} x ����
 * @param {uint16_t} y
 * @param {uint16_t} color ��ɫ
 * @return {*}
 */
void LCD_Fast_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    if (g_lcddev.id == 0X5510)
    {
        taskENTER_CRITICAL();

        LCD_WR_REG(g_lcddev.setxcmd);
        LCD_WR_DATA(x >> 8);
        LCD_WR_REG(g_lcddev.setxcmd + 1);
        LCD_WR_DATA(x & 0XFF);
        LCD_WR_REG(g_lcddev.setycmd);
        LCD_WR_DATA(y >> 8);
        LCD_WR_REG(g_lcddev.setycmd + 1);
        LCD_WR_DATA(y & 0XFF);
    }

    LCD->LCD_REG = g_lcddev.wramcmd;
    LCD->LCD_RAM = color;

    taskEXIT_CRITICAL();
}

/**
 * @description: SSD1963 ��������
 * @param {uint8_t} pwm ����ȼ�,0~100.Խ��Խ��
 * @return {*}
 */
void LCD_SSD_BackLightSet(uint8_t pwm)
{
    LCD_WR_REG(0xBE);        //����PWM���
    LCD_WR_DATA(0x05);       //1����PWMƵ��
    LCD_WR_DATA(pwm * 2.55); //2����PWMռ�ձ�
    LCD_WR_DATA(0x01);       //3����C
    LCD_WR_DATA(0xFF);       //4����D
    LCD_WR_DATA(0x00);       //5����E
    LCD_WR_DATA(0x00);       //6����F
}

/**
 * @description: ����LCD��ʾ����
 * @param {uint8_t} dir 0,������1,����
 * @return {*}
 */
void LCD_Display_Dir(uint8_t dir)
{
    if (dir == 0) //����
    {
        g_lcddev.wramcmd = 0X2C00;
        g_lcddev.setxcmd = 0X2A00;
        g_lcddev.setycmd = 0X2B00;
        g_lcddev.width = 480;
        g_lcddev.height = 800;
        g_lcddev.dir = 0;
    }
    else //����
    {
        g_lcddev.wramcmd = 0X2C00;
        g_lcddev.setxcmd = 0X2A00;
        g_lcddev.setycmd = 0X2B00;
        g_lcddev.width = 800;
        g_lcddev.height = 480;
        g_lcddev.dir = 1;
    }
    LCD_Scan_Dir(D2U_L2R);
}

/**
 * @description: ���ô���,���Զ����û������굽�������Ͻ�(sx,sy)
 * @param {uint16_t} sx sx,sy:������ʼ����(���Ͻ�)
 * @param {uint16_t} sy
 * @param {uint16_t} width width,height:���ڿ�Ⱥ͸߶�,�������0
 * @param {uint16_t} height 
 * @return {*}
 */
void LCD_Set_Window(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)
{
    uint16_t twidth, theight;
    twidth = sx + width - 1;
    theight = sy + height - 1;

    LCD_WR_REG(g_lcddev.setxcmd);
    LCD_WR_DATA(sx >> 8);
    LCD_WR_REG(g_lcddev.setxcmd + 1);
    LCD_WR_DATA(sx & 0XFF);
    LCD_WR_REG(g_lcddev.setxcmd + 2);
    LCD_WR_DATA(twidth >> 8);
    LCD_WR_REG(g_lcddev.setxcmd + 3);
    LCD_WR_DATA(twidth & 0XFF);
    LCD_WR_REG(g_lcddev.setycmd);
    LCD_WR_DATA(sy >> 8);
    LCD_WR_REG(g_lcddev.setycmd + 1);
    LCD_WR_DATA(sy & 0XFF);
    LCD_WR_REG(g_lcddev.setycmd + 2);
    LCD_WR_DATA(theight >> 8);
    LCD_WR_REG(g_lcddev.setycmd + 3);
    LCD_WR_DATA(theight & 0XFF);
}

/**
 * @description: ��������
 * @param {uint16_t} color Ҫ���������ɫ
 * @return {*}
 */
void LCD_Clear(uint16_t color)
{
    uint32_t index = 0;
    uint32_t totalpoint = g_lcddev.width;
    totalpoint *= g_lcddev.height; //�õ��ܵ���
    LCD_SetCursor(0x00, 0x0000);   //���ù��λ��
    LCD_WriteRAM_Prepare();        //��ʼд��GRAM
    for (index = 0; index < totalpoint; index++)
    {
        LCD->LCD_RAM = color;
    }
}

/**
 * @description: ��ָ����������䵥����ɫ
 * @param {uint16_t} sx (sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)
 * @param {uint16_t} sy
 * @param {uint16_t} ex
 * @param {uint16_t} ey
 * @param {uint16_t} color Ҫ������ɫ
 * @return {*}
 */
void LCD_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
    uint16_t i, j;
    uint16_t xlen = 0;
    xlen = ex - sx + 1;
    for (i = sy; i <= ey; i++)
    {
        LCD_SetCursor(sx, i);   //���ù��λ��
        LCD_WriteRAM_Prepare(); //��ʼд��GRAM
        for (j = 0; j < xlen; j++)
            LCD->LCD_RAM = color; //��ʾ��ɫ
    }
}

/**
 * @description: ��ָ�����������ָ����ɫ��
 * @param {uint16_t} sx (sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)
 * @param {uint16_t} sy
 * @param {uint16_t} ex
 * @param {uint16_t} ey
 * @param {uint16_t} *color Ҫ������ɫ
 * @return {*}
 */
void LCD_Color_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color)
{
    uint16_t height, width;
    uint16_t i, j;
    width = ex - sx + 1;  //�õ����Ŀ��
    height = ey - sy + 1; //�߶�
    for (i = 0; i < height; i++)
    {
        LCD_SetCursor(sx, sy + i); //���ù��λ��
        LCD_WriteRAM_Prepare();    //��ʼд��GRAM
        for (j = 0; j < width; j++)
            LCD->LCD_RAM = color[i * width + j]; //д������
    }
}

/**
 * @description: ����
 * @param {uint16_t} x1 x1,y1:�������
 * @param {uint16_t} y1
 * @param {uint16_t} x2 x2,y2:�յ�����
 * @param {uint16_t} y2
 * @return {*}
 */
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1; //������������
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if (delta_x > 0)
        incx = 1; //���õ�������
    else if (delta_x == 0)
        incx = 0; //��ֱ��
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; //ˮƽ��
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x; //ѡȡ��������������
    else
        distance = delta_y;
    for (t = 0; t <= distance + 1; t++) //�������
    {
        LCD_DrawPoint(uRow, uCol); //����
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

/**
 * @description: ������
 * @param {uint16_t} x1 (x1,y1),(x2,y2):���εĶԽ�����
 * @param {uint16_t} y1
 * @param {uint16_t} x2
 * @param {uint16_t} y2
 * @return {*}
 */
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    LCD_DrawLine(x1, y1, x2, y1);
    LCD_DrawLine(x1, y1, x1, y2);
    LCD_DrawLine(x1, y2, x2, y2);
    LCD_DrawLine(x2, y1, x2, y2);
}

/**
 * @description: ��ָ��λ�û�һ��ָ����С��Բ
 * @param {uint16_t} x0 ���ĵ�
 * @param {uint16_t} y0
 * @param {uint8_t} r �뾶
 * @return {*}
 */
void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r)
{
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1); //�ж��¸���λ�õı�־
    while (a <= b)
    {
        LCD_DrawPoint(x0 + a, y0 - b); //5
        LCD_DrawPoint(x0 + b, y0 - a); //0
        LCD_DrawPoint(x0 + b, y0 + a); //4
        LCD_DrawPoint(x0 + a, y0 + b); //6
        LCD_DrawPoint(x0 - a, y0 + b); //1
        LCD_DrawPoint(x0 - b, y0 + a);
        LCD_DrawPoint(x0 - a, y0 - b); //2
        LCD_DrawPoint(x0 - b, y0 - a); //7
        a++;
        //ʹ��Bresenham�㷨��Բ
        if (di < 0)
            di += 4 * a + 6;
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}
/**
 * @description: 
 * @param {uint16_t} x0
 * @param {uint16_t} y0
 * @param {uint8_t} r
 * @return {*}
 */
void LCD_Draw_Circle_Fill(uint16_t x0, uint16_t y0, uint8_t r)
{
    uint16_t x, y;
    for (y = y0 - r; y < y0 + r; y++)
    {
        for (x = x0 - r; x < x0 + r; x++)
        {
            if (((x - x0) * (x - x0) + (y - y0) * (y - y0)) <= r * r)
            {
                LCD_DrawPoint(x, y);
            }
        }
    }
}
/**
 * @description: ��ָ��λ����ʾһ���ַ�
 * @param {uint16_t} x ��ʼ����
 * @param {uint16_t} y
 * @param {uint8_t} num Ҫ��ʾ���ַ�
 * @param {uint8_t} size �����С 12/16/24
 * @param {uint8_t} mode ���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
 * @return {*}
 */
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint8_t mode)
{
    uint8_t temp, t1, t;
    uint16_t y0 = y;
    uint8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2); //�õ�����һ���ַ���Ӧ������ռ���ֽ���
    // uint16_t currentColor = 0;
    num = num - ' '; //�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
    for (t = 0; t < csize; t++)
    {
        if (size == 12)
            temp = asc2_1206[num][t]; //����1206����
        else if (size == 16)
            temp = asc2_1608[num][t]; //����1608����
        else if (size == 24)
            temp = asc2_2412[num][t]; //����2412����
        else
            return; //û�е��ֿ�
        for (t1 = 0; t1 < 8; t1++)
        {
            if (temp & 0x80)
                LCD_Fast_DrawPoint(x, y, POINT_COLOR);
            else if (mode == 0)
            {
                // currentColor = LCD_ReadPoint(x, y);
                LCD_Fast_DrawPoint(x, y, BACK_COLOR);
                // LCD_Fast_DrawPoint(x, y, currentColor);
            }
            temp <<= 1;
            y++;
            if (y >= g_lcddev.height)
                return; //��������
            if ((y - y0) == size)
            {
                y = y0;
                x++;
                if (x >= g_lcddev.width)
                    return; //��������
                break;
            }
        }
    }
}

/**
 * @description: m^n����
 * @param {uint8_t} m 
 * @param {uint8_t} n
 * @return {*} m^n�η�
 */
uint32_t LCD_Pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
        result *= m;
    return result;
}

/**
 * @description: ��ʾ����,��λΪ0,����ʾ
 * @param {uint16_t} x �������
 * @param {uint16_t} y
 * @param {uint32_t} num ���ֵ�λ��
 * @param {uint8_t} len  �����С
 * @param {uint8_t} size ��ɫ
 * @return {*}
 */
void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size)
{
    uint8_t t, temp;
    uint8_t enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / LCD_Pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                LCD_ShowChar(x + (size / 2) * t, y, ' ', size, 0);
                continue;
            }
            else
                enshow = 1;
        }
        LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, 0);
    }
}

/**
 * @description: ��ʾ����,��λΪ0
 * @param {uint16_t} x �������
 * @param {uint16_t} y
 * @param {uint32_t} num ��ֵ
 * @param {uint8_t} len ����
 * @param {uint8_t} size �����С
 * @param {uint8_t} mode [7]:0,�����;1,���0; [6:1]:����; [0]:0,�ǵ�����ʾ;1,������ʾ
 * @return {*}
 */
void LCD_ShowxNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode)
{
    uint8_t t, temp;
    uint8_t enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / LCD_Pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                if (mode & 0X80)
                    LCD_ShowChar(x + (size / 2) * t, y, '0', size, mode & 0X01);
                else
                    LCD_ShowChar(x + (size / 2) * t, y, ' ', size, mode & 0X01);
                continue;
            }
            else
                enshow = 1;
        }
        LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, mode & 0X01);
    }
}

/**
 * @description: ��ʾ�ַ���
 * @param {uint16_t} x �������
 * @param {uint16_t} y
 * @param {uint16_t} width �����С
 * @param {uint16_t} height
 * @param {uint8_t} size �����С
 * @param {uint8_t} *p �ַ�����ʼ��ַ
 * @return {*}
 */
void LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint8_t *p)
{
    uint8_t x0 = x;
    width += x;
    height += y;
    while ((*p <= '~') && (*p >= ' ')) //�ж��ǲ��ǷǷ��ַ�!
    {
        if (x >= width)
        {
            x = x0;
            y += size;
        }
        if (y >= height)
            break; //�˳�
        LCD_ShowChar(x, y, *p, size, 0);
        x += size / 2;
        p++;
    }
}
/**
 * @description: ��ָ��������ʾ��ɫ
 * @param {uint16_t} x
 * @param {uint16_t} y
 * @param {uint16_t} color
 * @return {*}
 */
void LCD_DrawPoint_pic(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_SetCursor(x, y);    //���ù��λ��
    LCD_WriteRAM_Prepare(); //��ʼд��GRAM
    LCD->LCD_RAM = color;
}

/**
 * @description: ��ָ�����귶Χ��ʾһ��ͼƬ,ͼƬȡģ��ʽΪˮƽɨ�裬16λ��ɫģʽ, ��Ҫ��ͼƬ����ת��Ϊ����
 * @param {uint16_t} StartX ����ʼ����
 * @param {uint16_t} StartY ����ʼ����
 * @param {uint16_t} Xend   �н�������
 * @param {uint16_t} Yend   �н�������
 * @param {uint8_t} *pic    ͼƬͷָ��
 * @return {*}
 */
void LCD_DrawPicture(uint16_t StartX, uint16_t StartY, uint16_t Xend, uint16_t Yend, uint8_t *pic)
{
    static uint16_t i = 0, j = 0;
    uint16_t *bitmap = (uint16_t *)pic;
    for (j = 0; j < Yend - StartY; j++)
    {
        for (i = 0; i < Xend - StartX; i++)
            LCD_DrawPoint_pic(StartX + i, StartY + j, *bitmap++);
    }
}

/**
 * @description: ��LCD��д����
 * @param {uint8_t} cmd ����
 * @return {*}
 */
void LCD_Write_Cmd(uint8_t cmd)
{
    LCD->LCD_REG = cmd; //д��Ҫд�ļĴ������
}

/**
 * @description: ��LCD��д����
 * @param {uint8_t} data ����
 * @return {*}
 */
void LCD_Write_Data(uint8_t data)
{
    LCD->LCD_RAM = data; //д������
}

/**
 * @description: ��ʼ��LCD
 * @param {*}
 * @return {*}
 */
void LCD_Init(void)
{
    HAL_Delay(50); // delay 50 ms
    LCD_WriteReg(0x0000, 0x0001);
    HAL_Delay(50); // delay 50 ms

    {
        //��������дʱ����ƼĴ�����ʱ��
        FSMC_Bank1E->BWTR[6] &= ~(0XF << 0); //��ַ����ʱ��(ADDSET)����
        FSMC_Bank1E->BWTR[6] &= ~(0XF << 8); //���ݱ���ʱ������
        FSMC_Bank1E->BWTR[6] |= 3 << 0;      //��ַ����ʱ��(ADDSET)Ϊ3��HCLK =18ns
        FSMC_Bank1E->BWTR[6] |= 2 << 8;      //���ݱ���ʱ��(DATAST)Ϊ6ns*3��HCLK=18ns
    }
    g_lcddev.id = 0x5510;
    CONSOLE_INFO("LCD ID:%x", g_lcddev.id); //��ӡLCD ID

    {
        LCD_WriteReg(0xF000, 0x55);
        LCD_WriteReg(0xF001, 0xAA);
        LCD_WriteReg(0xF002, 0x52);
        LCD_WriteReg(0xF003, 0x08);
        LCD_WriteReg(0xF004, 0x01);
        //AVDD Set AVDD 5.2V
        LCD_WriteReg(0xB000, 0x0D);
        LCD_WriteReg(0xB001, 0x0D);
        LCD_WriteReg(0xB002, 0x0D);
        //AVDD ratio
        LCD_WriteReg(0xB600, 0x34);
        LCD_WriteReg(0xB601, 0x34);
        LCD_WriteReg(0xB602, 0x34);
        //AVEE -5.2V
        LCD_WriteReg(0xB100, 0x0D);
        LCD_WriteReg(0xB101, 0x0D);
        LCD_WriteReg(0xB102, 0x0D);
        //AVEE ratio
        LCD_WriteReg(0xB700, 0x34);
        LCD_WriteReg(0xB701, 0x34);
        LCD_WriteReg(0xB702, 0x34);
        //VCL -2.5V
        LCD_WriteReg(0xB200, 0x00);
        LCD_WriteReg(0xB201, 0x00);
        LCD_WriteReg(0xB202, 0x00);
        //VCL ratio
        LCD_WriteReg(0xB800, 0x24);
        LCD_WriteReg(0xB801, 0x24);
        LCD_WriteReg(0xB802, 0x24);
        //VGH 15V (Free pump)
        LCD_WriteReg(0xBF00, 0x01);
        LCD_WriteReg(0xB300, 0x0F);
        LCD_WriteReg(0xB301, 0x0F);
        LCD_WriteReg(0xB302, 0x0F);
        //VGH ratio
        LCD_WriteReg(0xB900, 0x34);
        LCD_WriteReg(0xB901, 0x34);
        LCD_WriteReg(0xB902, 0x34);
        //VGL_REG -10V
        LCD_WriteReg(0xB500, 0x08);
        LCD_WriteReg(0xB501, 0x08);
        LCD_WriteReg(0xB502, 0x08);
        LCD_WriteReg(0xC200, 0x03);
        //VGLX ratio
        LCD_WriteReg(0xBA00, 0x24);
        LCD_WriteReg(0xBA01, 0x24);
        LCD_WriteReg(0xBA02, 0x24);
        //VGMP/VGSP 4.5V/0V
        LCD_WriteReg(0xBC00, 0x00);
        LCD_WriteReg(0xBC01, 0x78);
        LCD_WriteReg(0xBC02, 0x00);
        //VGMN/VGSN -4.5V/0V
        LCD_WriteReg(0xBD00, 0x00);
        LCD_WriteReg(0xBD01, 0x78);
        LCD_WriteReg(0xBD02, 0x00);
        //VCOM
        LCD_WriteReg(0xBE00, 0x00);
        LCD_WriteReg(0xBE01, 0x64);
        //Gamma Setting
        LCD_WriteReg(0xD100, 0x00);
        LCD_WriteReg(0xD101, 0x33);
        LCD_WriteReg(0xD102, 0x00);
        LCD_WriteReg(0xD103, 0x34);
        LCD_WriteReg(0xD104, 0x00);
        LCD_WriteReg(0xD105, 0x3A);
        LCD_WriteReg(0xD106, 0x00);
        LCD_WriteReg(0xD107, 0x4A);
        LCD_WriteReg(0xD108, 0x00);
        LCD_WriteReg(0xD109, 0x5C);
        LCD_WriteReg(0xD10A, 0x00);
        LCD_WriteReg(0xD10B, 0x81);
        LCD_WriteReg(0xD10C, 0x00);
        LCD_WriteReg(0xD10D, 0xA6);
        LCD_WriteReg(0xD10E, 0x00);
        LCD_WriteReg(0xD10F, 0xE5);
        LCD_WriteReg(0xD110, 0x01);
        LCD_WriteReg(0xD111, 0x13);
        LCD_WriteReg(0xD112, 0x01);
        LCD_WriteReg(0xD113, 0x54);
        LCD_WriteReg(0xD114, 0x01);
        LCD_WriteReg(0xD115, 0x82);
        LCD_WriteReg(0xD116, 0x01);
        LCD_WriteReg(0xD117, 0xCA);
        LCD_WriteReg(0xD118, 0x02);
        LCD_WriteReg(0xD119, 0x00);
        LCD_WriteReg(0xD11A, 0x02);
        LCD_WriteReg(0xD11B, 0x01);
        LCD_WriteReg(0xD11C, 0x02);
        LCD_WriteReg(0xD11D, 0x34);
        LCD_WriteReg(0xD11E, 0x02);
        LCD_WriteReg(0xD11F, 0x67);
        LCD_WriteReg(0xD120, 0x02);
        LCD_WriteReg(0xD121, 0x84);
        LCD_WriteReg(0xD122, 0x02);
        LCD_WriteReg(0xD123, 0xA4);
        LCD_WriteReg(0xD124, 0x02);
        LCD_WriteReg(0xD125, 0xB7);
        LCD_WriteReg(0xD126, 0x02);
        LCD_WriteReg(0xD127, 0xCF);
        LCD_WriteReg(0xD128, 0x02);
        LCD_WriteReg(0xD129, 0xDE);
        LCD_WriteReg(0xD12A, 0x02);
        LCD_WriteReg(0xD12B, 0xF2);
        LCD_WriteReg(0xD12C, 0x02);
        LCD_WriteReg(0xD12D, 0xFE);
        LCD_WriteReg(0xD12E, 0x03);
        LCD_WriteReg(0xD12F, 0x10);
        LCD_WriteReg(0xD130, 0x03);
        LCD_WriteReg(0xD131, 0x33);
        LCD_WriteReg(0xD132, 0x03);
        LCD_WriteReg(0xD133, 0x6D);

        LCD_WriteReg(0xD200, 0x00);
        LCD_WriteReg(0xD201, 0x33);
        LCD_WriteReg(0xD202, 0x00);
        LCD_WriteReg(0xD203, 0x34);
        LCD_WriteReg(0xD204, 0x00);
        LCD_WriteReg(0xD205, 0x3A);
        LCD_WriteReg(0xD206, 0x00);
        LCD_WriteReg(0xD207, 0x4A);
        LCD_WriteReg(0xD208, 0x00);
        LCD_WriteReg(0xD209, 0x5C);
        LCD_WriteReg(0xD20A, 0x00);
        LCD_WriteReg(0xD20B, 0x81);
        LCD_WriteReg(0xD20C, 0x00);
        LCD_WriteReg(0xD20D, 0xA6);
        LCD_WriteReg(0xD20E, 0x00);
        LCD_WriteReg(0xD20F, 0xE5);
        LCD_WriteReg(0xD210, 0x01);
        LCD_WriteReg(0xD211, 0x13);
        LCD_WriteReg(0xD212, 0x01);
        LCD_WriteReg(0xD213, 0x54);
        LCD_WriteReg(0xD214, 0x01);
        LCD_WriteReg(0xD215, 0x82);
        LCD_WriteReg(0xD216, 0x01);
        LCD_WriteReg(0xD217, 0xCA);
        LCD_WriteReg(0xD218, 0x02);
        LCD_WriteReg(0xD219, 0x00);
        LCD_WriteReg(0xD21A, 0x02);
        LCD_WriteReg(0xD21B, 0x01);
        LCD_WriteReg(0xD21C, 0x02);
        LCD_WriteReg(0xD21D, 0x34);
        LCD_WriteReg(0xD21E, 0x02);
        LCD_WriteReg(0xD21F, 0x67);
        LCD_WriteReg(0xD220, 0x02);
        LCD_WriteReg(0xD221, 0x84);
        LCD_WriteReg(0xD222, 0x02);
        LCD_WriteReg(0xD223, 0xA4);
        LCD_WriteReg(0xD224, 0x02);
        LCD_WriteReg(0xD225, 0xB7);
        LCD_WriteReg(0xD226, 0x02);
        LCD_WriteReg(0xD227, 0xCF);
        LCD_WriteReg(0xD228, 0x02);
        LCD_WriteReg(0xD229, 0xDE);
        LCD_WriteReg(0xD22A, 0x02);
        LCD_WriteReg(0xD22B, 0xF2);
        LCD_WriteReg(0xD22C, 0x02);
        LCD_WriteReg(0xD22D, 0xFE);
        LCD_WriteReg(0xD22E, 0x03);
        LCD_WriteReg(0xD22F, 0x10);
        LCD_WriteReg(0xD230, 0x03);
        LCD_WriteReg(0xD231, 0x33);
        LCD_WriteReg(0xD232, 0x03);
        LCD_WriteReg(0xD233, 0x6D);

        LCD_WriteReg(0xD300, 0x00);
        LCD_WriteReg(0xD301, 0x33);
        LCD_WriteReg(0xD302, 0x00);
        LCD_WriteReg(0xD303, 0x34);
        LCD_WriteReg(0xD304, 0x00);
        LCD_WriteReg(0xD305, 0x3A);
        LCD_WriteReg(0xD306, 0x00);
        LCD_WriteReg(0xD307, 0x4A);
        LCD_WriteReg(0xD308, 0x00);
        LCD_WriteReg(0xD309, 0x5C);
        LCD_WriteReg(0xD30A, 0x00);
        LCD_WriteReg(0xD30B, 0x81);
        LCD_WriteReg(0xD30C, 0x00);
        LCD_WriteReg(0xD30D, 0xA6);
        LCD_WriteReg(0xD30E, 0x00);
        LCD_WriteReg(0xD30F, 0xE5);
        LCD_WriteReg(0xD310, 0x01);
        LCD_WriteReg(0xD311, 0x13);
        LCD_WriteReg(0xD312, 0x01);
        LCD_WriteReg(0xD313, 0x54);
        LCD_WriteReg(0xD314, 0x01);
        LCD_WriteReg(0xD315, 0x82);
        LCD_WriteReg(0xD316, 0x01);
        LCD_WriteReg(0xD317, 0xCA);
        LCD_WriteReg(0xD318, 0x02);
        LCD_WriteReg(0xD319, 0x00);
        LCD_WriteReg(0xD31A, 0x02);
        LCD_WriteReg(0xD31B, 0x01);
        LCD_WriteReg(0xD31C, 0x02);
        LCD_WriteReg(0xD31D, 0x34);
        LCD_WriteReg(0xD31E, 0x02);
        LCD_WriteReg(0xD31F, 0x67);
        LCD_WriteReg(0xD320, 0x02);
        LCD_WriteReg(0xD321, 0x84);
        LCD_WriteReg(0xD322, 0x02);
        LCD_WriteReg(0xD323, 0xA4);
        LCD_WriteReg(0xD324, 0x02);
        LCD_WriteReg(0xD325, 0xB7);
        LCD_WriteReg(0xD326, 0x02);
        LCD_WriteReg(0xD327, 0xCF);
        LCD_WriteReg(0xD328, 0x02);
        LCD_WriteReg(0xD329, 0xDE);
        LCD_WriteReg(0xD32A, 0x02);
        LCD_WriteReg(0xD32B, 0xF2);
        LCD_WriteReg(0xD32C, 0x02);
        LCD_WriteReg(0xD32D, 0xFE);
        LCD_WriteReg(0xD32E, 0x03);
        LCD_WriteReg(0xD32F, 0x10);
        LCD_WriteReg(0xD330, 0x03);
        LCD_WriteReg(0xD331, 0x33);
        LCD_WriteReg(0xD332, 0x03);
        LCD_WriteReg(0xD333, 0x6D);

        LCD_WriteReg(0xD400, 0x00);
        LCD_WriteReg(0xD401, 0x33);
        LCD_WriteReg(0xD402, 0x00);
        LCD_WriteReg(0xD403, 0x34);
        LCD_WriteReg(0xD404, 0x00);
        LCD_WriteReg(0xD405, 0x3A);
        LCD_WriteReg(0xD406, 0x00);
        LCD_WriteReg(0xD407, 0x4A);
        LCD_WriteReg(0xD408, 0x00);
        LCD_WriteReg(0xD409, 0x5C);
        LCD_WriteReg(0xD40A, 0x00);
        LCD_WriteReg(0xD40B, 0x81);
        LCD_WriteReg(0xD40C, 0x00);
        LCD_WriteReg(0xD40D, 0xA6);
        LCD_WriteReg(0xD40E, 0x00);
        LCD_WriteReg(0xD40F, 0xE5);
        LCD_WriteReg(0xD410, 0x01);
        LCD_WriteReg(0xD411, 0x13);
        LCD_WriteReg(0xD412, 0x01);
        LCD_WriteReg(0xD413, 0x54);
        LCD_WriteReg(0xD414, 0x01);
        LCD_WriteReg(0xD415, 0x82);
        LCD_WriteReg(0xD416, 0x01);
        LCD_WriteReg(0xD417, 0xCA);
        LCD_WriteReg(0xD418, 0x02);
        LCD_WriteReg(0xD419, 0x00);
        LCD_WriteReg(0xD41A, 0x02);
        LCD_WriteReg(0xD41B, 0x01);
        LCD_WriteReg(0xD41C, 0x02);
        LCD_WriteReg(0xD41D, 0x34);
        LCD_WriteReg(0xD41E, 0x02);
        LCD_WriteReg(0xD41F, 0x67);
        LCD_WriteReg(0xD420, 0x02);
        LCD_WriteReg(0xD421, 0x84);
        LCD_WriteReg(0xD422, 0x02);
        LCD_WriteReg(0xD423, 0xA4);
        LCD_WriteReg(0xD424, 0x02);
        LCD_WriteReg(0xD425, 0xB7);
        LCD_WriteReg(0xD426, 0x02);
        LCD_WriteReg(0xD427, 0xCF);
        LCD_WriteReg(0xD428, 0x02);
        LCD_WriteReg(0xD429, 0xDE);
        LCD_WriteReg(0xD42A, 0x02);
        LCD_WriteReg(0xD42B, 0xF2);
        LCD_WriteReg(0xD42C, 0x02);
        LCD_WriteReg(0xD42D, 0xFE);
        LCD_WriteReg(0xD42E, 0x03);
        LCD_WriteReg(0xD42F, 0x10);
        LCD_WriteReg(0xD430, 0x03);
        LCD_WriteReg(0xD431, 0x33);
        LCD_WriteReg(0xD432, 0x03);
        LCD_WriteReg(0xD433, 0x6D);

        LCD_WriteReg(0xD500, 0x00);
        LCD_WriteReg(0xD501, 0x33);
        LCD_WriteReg(0xD502, 0x00);
        LCD_WriteReg(0xD503, 0x34);
        LCD_WriteReg(0xD504, 0x00);
        LCD_WriteReg(0xD505, 0x3A);
        LCD_WriteReg(0xD506, 0x00);
        LCD_WriteReg(0xD507, 0x4A);
        LCD_WriteReg(0xD508, 0x00);
        LCD_WriteReg(0xD509, 0x5C);
        LCD_WriteReg(0xD50A, 0x00);
        LCD_WriteReg(0xD50B, 0x81);
        LCD_WriteReg(0xD50C, 0x00);
        LCD_WriteReg(0xD50D, 0xA6);
        LCD_WriteReg(0xD50E, 0x00);
        LCD_WriteReg(0xD50F, 0xE5);
        LCD_WriteReg(0xD510, 0x01);
        LCD_WriteReg(0xD511, 0x13);
        LCD_WriteReg(0xD512, 0x01);
        LCD_WriteReg(0xD513, 0x54);
        LCD_WriteReg(0xD514, 0x01);
        LCD_WriteReg(0xD515, 0x82);
        LCD_WriteReg(0xD516, 0x01);
        LCD_WriteReg(0xD517, 0xCA);
        LCD_WriteReg(0xD518, 0x02);
        LCD_WriteReg(0xD519, 0x00);
        LCD_WriteReg(0xD51A, 0x02);
        LCD_WriteReg(0xD51B, 0x01);
        LCD_WriteReg(0xD51C, 0x02);
        LCD_WriteReg(0xD51D, 0x34);
        LCD_WriteReg(0xD51E, 0x02);
        LCD_WriteReg(0xD51F, 0x67);
        LCD_WriteReg(0xD520, 0x02);
        LCD_WriteReg(0xD521, 0x84);
        LCD_WriteReg(0xD522, 0x02);
        LCD_WriteReg(0xD523, 0xA4);
        LCD_WriteReg(0xD524, 0x02);
        LCD_WriteReg(0xD525, 0xB7);
        LCD_WriteReg(0xD526, 0x02);
        LCD_WriteReg(0xD527, 0xCF);
        LCD_WriteReg(0xD528, 0x02);
        LCD_WriteReg(0xD529, 0xDE);
        LCD_WriteReg(0xD52A, 0x02);
        LCD_WriteReg(0xD52B, 0xF2);
        LCD_WriteReg(0xD52C, 0x02);
        LCD_WriteReg(0xD52D, 0xFE);
        LCD_WriteReg(0xD52E, 0x03);
        LCD_WriteReg(0xD52F, 0x10);
        LCD_WriteReg(0xD530, 0x03);
        LCD_WriteReg(0xD531, 0x33);
        LCD_WriteReg(0xD532, 0x03);
        LCD_WriteReg(0xD533, 0x6D);

        LCD_WriteReg(0xD600, 0x00);
        LCD_WriteReg(0xD601, 0x33);
        LCD_WriteReg(0xD602, 0x00);
        LCD_WriteReg(0xD603, 0x34);
        LCD_WriteReg(0xD604, 0x00);
        LCD_WriteReg(0xD605, 0x3A);
        LCD_WriteReg(0xD606, 0x00);
        LCD_WriteReg(0xD607, 0x4A);
        LCD_WriteReg(0xD608, 0x00);
        LCD_WriteReg(0xD609, 0x5C);
        LCD_WriteReg(0xD60A, 0x00);
        LCD_WriteReg(0xD60B, 0x81);
        LCD_WriteReg(0xD60C, 0x00);
        LCD_WriteReg(0xD60D, 0xA6);
        LCD_WriteReg(0xD60E, 0x00);
        LCD_WriteReg(0xD60F, 0xE5);
        LCD_WriteReg(0xD610, 0x01);
        LCD_WriteReg(0xD611, 0x13);
        LCD_WriteReg(0xD612, 0x01);
        LCD_WriteReg(0xD613, 0x54);
        LCD_WriteReg(0xD614, 0x01);
        LCD_WriteReg(0xD615, 0x82);
        LCD_WriteReg(0xD616, 0x01);
        LCD_WriteReg(0xD617, 0xCA);
        LCD_WriteReg(0xD618, 0x02);
        LCD_WriteReg(0xD619, 0x00);
        LCD_WriteReg(0xD61A, 0x02);
        LCD_WriteReg(0xD61B, 0x01);
        LCD_WriteReg(0xD61C, 0x02);
        LCD_WriteReg(0xD61D, 0x34);
        LCD_WriteReg(0xD61E, 0x02);
        LCD_WriteReg(0xD61F, 0x67);
        LCD_WriteReg(0xD620, 0x02);
        LCD_WriteReg(0xD621, 0x84);
        LCD_WriteReg(0xD622, 0x02);
        LCD_WriteReg(0xD623, 0xA4);
        LCD_WriteReg(0xD624, 0x02);
        LCD_WriteReg(0xD625, 0xB7);
        LCD_WriteReg(0xD626, 0x02);
        LCD_WriteReg(0xD627, 0xCF);
        LCD_WriteReg(0xD628, 0x02);
        LCD_WriteReg(0xD629, 0xDE);
        LCD_WriteReg(0xD62A, 0x02);
        LCD_WriteReg(0xD62B, 0xF2);
        LCD_WriteReg(0xD62C, 0x02);
        LCD_WriteReg(0xD62D, 0xFE);
        LCD_WriteReg(0xD62E, 0x03);
        LCD_WriteReg(0xD62F, 0x10);
        LCD_WriteReg(0xD630, 0x03);
        LCD_WriteReg(0xD631, 0x33);
        LCD_WriteReg(0xD632, 0x03);
        LCD_WriteReg(0xD633, 0x6D);
        //LV2 Page 0 enable
        LCD_WriteReg(0xF000, 0x55);
        LCD_WriteReg(0xF001, 0xAA);
        LCD_WriteReg(0xF002, 0x52);
        LCD_WriteReg(0xF003, 0x08);
        LCD_WriteReg(0xF004, 0x00);

        //480*800
        //	LCD_WriteReg(0xB500, 0x50);///////////////////////////////////////////////////////
        //Display control
        LCD_WriteReg(0xB100, 0xCC);
        LCD_WriteReg(0xB101, 0x00);
        //Source hold time
        LCD_WriteReg(0xB600, 0x05);
        //Gate EQ control
        LCD_WriteReg(0xB700, 0x70);
        LCD_WriteReg(0xB701, 0x70);
        //Source EQ control (Mode 2)
        LCD_WriteReg(0xB800, 0x01);
        LCD_WriteReg(0xB801, 0x03);
        LCD_WriteReg(0xB802, 0x03);
        LCD_WriteReg(0xB803, 0x03);
        //Inversion mode (2-dot)
        LCD_WriteReg(0xBC00, 0x02);
        LCD_WriteReg(0xBC01, 0x00);
        LCD_WriteReg(0xBC02, 0x00);

        //Frame rate	(Nova non-used)
        //		LCD_WriteReg(0xBD00,0x01);//////////////////////////////////////////////////////
        //		LCD_WriteReg(0xBD01,0x84);//////////////////////////////////////////////////////
        //		LCD_WriteReg(0xBD02,0x1C);//////////////////////////////////////////////////////
        //		LCD_WriteReg(0xBD03,0x1C);//////////////////////////////////////////////////////
        //		LCD_WriteReg(0xBD04,0x00);//////////////////////////////////////////////////////

        //Timing control 4H w/ 4-delay
        LCD_WriteReg(0xC900, 0xD0);
        LCD_WriteReg(0xC901, 0x02);
        LCD_WriteReg(0xC902, 0x50);
        LCD_WriteReg(0xC903, 0x50);
        LCD_WriteReg(0xC904, 0x50);

        //	LCD_WriteReg(0x3600,0x00);//////////////////////////////////////////////
        LCD_WriteReg(0x3500, 0x00);

        //		LCD_WriteReg(0xFF00,0xAA);//////////////////////////////////////////////
        //		LCD_WriteReg(0xFF01,0x55);//////////////////////////////////////////////
        //		LCD_WriteReg(0xFF02,0x25);//////////////////////////////////////////////
        //		LCD_WriteReg(0xFF03,0x01);//////////////////////////////////////////////
        //
        //		LCD_WriteReg(0xFC00,0xAA);//////////////////////////////////////////////
        //		LCD_WriteReg(0xFC01,0xAA);//////////////////////////////////////////////
        //		LCD_WriteReg(0xFC02,0xAA);//////////////////////////////////////////////
        //		LCD_WriteReg(0x3A00,0x06);//////////////////////////////////////////////

        LCD_WriteReg(0x3500, 0x00);
        LCD_WriteReg(0x3A00, 0x55); //16-bit/pixel
        LCD_WR_REG(0x1100);
        delay_us(160);
        LCD_WR_REG(0x2900);
    }

    LCD_Display_Dir(1); //dir:0,������1,����

    LCD_Clear(LIGHTGREEN);
}
