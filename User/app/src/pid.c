#include "pid.h"


static Pid_t tPidSpeedA;
static Pid_t tPidSpeedB;
static Pid_t tPidSpeedC;
static Pid_t tPidSpeedD;
/*
*********************************************************************************************************
*	�� �� ��: PID_Init
*	����˵��: ����4�����P��I��D��ֵ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitPid(void)
{
    tPidSpeedA.P = 1.5;
    tPidSpeedA.I = 0;
    tPidSpeedA.D = 0;

    tPidSpeedA.PrevError = 0;
    tPidSpeedA.SumError = 0;
    
    
    tPidSpeedB.P = 0.1;
    tPidSpeedB.I = 0.2;
    tPidSpeedB.D = 0.1;

    tPidSpeedB.PrevError = 0;
    tPidSpeedB.SumError = 0;

    tPidSpeedC.P = 0.1;
    tPidSpeedC.I = 0.2;
    tPidSpeedC.D = 0.1;
    tPidSpeedC.PrevError = 0;
    tPidSpeedC.SumError = 0;
    
    tPidSpeedD.P = 0.1;
    tPidSpeedD.I = 0.2;
    tPidSpeedD.D = 0.1;
    tPidSpeedD.PrevError = 0;
    tPidSpeedD.SumError = 0;
}
/*
*********************************************************************************************************
*	�� �� ��: wheelSpeedPidCalc
*	����˵��: ����PIDģ�ͼ�������pwmֵ
*	��    ��: _ucWheelNum������ _usMeasure ���ֵ�����������ĵ�����ٶȣ�   _usTarget Ŀ��ֵ���趨�ĵ�����ٶȣ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/

int wheelSpeedPidCalc(uint8_t _ucWheelNum, uint16_t _usMeasure, uint16_t _usTarget)
{
    float _dError = 0;
    float _error  = 0;
    float _tempP  = 0;
    float _tempI  = 0; 
    float _tempD  = 0; 
    float _tempPID = 0;
    
    Pid_t *_tpid; 
    switch(_ucWheelNum)
    {
        case 0:
          _tpid = &tPidSpeedA;  
        break;
        
        case 1:
          _tpid = &tPidSpeedB; 
        break;
        
        case 2:
           _tpid = &tPidSpeedC; 
        break;
        
        case 3:
            _tpid = &tPidSpeedD;
        break;
    
    }
    
    _error = _usTarget - _usMeasure;  /*���㵱ǰ���*/

    _tempP = _tpid->P * _error;/*����P���ֵ*/

    _tpid->SumError += _error;  /*�ۼ����*/
    
    _tempI = _tpid->I * _tpid->SumError;   /*����I���ֵ*/

    if(_tempI > 2000)
    {
        _tpid->SumError = 2000 / _tpid->I;
    }
    if(_tempI < -2000)
    {
        _tpid->SumError = -2000 / _tpid->I;
    }

    _dError = _error - _tpid->PrevError;/*΢�����*/
    
    _tempD  = _tpid->D * _dError;/*����D���ֵ*/

    _tpid->PrevError = _error ;
    
    _tempPID = _tempP + _tempI + _tempD;
    
    _tempPID = _tempPID;

    if(_tempPID > 2000)
    {
        _tempPID = 2000;
    }
    if(_tempPID < 0)
    {
        _tempPID  = 0;
    }
    
    return _tempPID;
}



/*
*********************************************************************************************************
*	�� �� ��: PID_Param_SetZero
*	����˵��: �Ե�����ۼ���� PrevError��0
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void PID_Param_SetZero(void)
{

    tPidSpeedA.PrevError = 0;
    tPidSpeedA.SumError = 0;
    
    tPidSpeedB.PrevError = 0;
    tPidSpeedB.SumError = 0;
    
    tPidSpeedC.PrevError = 0;
    tPidSpeedC.SumError = 0;
    
    tPidSpeedD.PrevError = 0;
    tPidSpeedD.SumError = 0;
}

