//
//  IMUSANT_segmented_part_LBDM_Expected.h
//  imusant
//
//  Created by Derrick Hill on 7/05/2016.
//
//

#ifndef imusant_IMUSANT_segmented_part_LBDM_Expected_h
#define imusant_IMUSANT_segmented_part_LBDM_Expected_h


class IMUSANT_segmented_part_LBDM_Expected
{

protected:
    
    bool equalWithinTollerance(float f1, float f2)
    {
        return (fabs(f1 - f2) < 0.001);
    }
    
    // ************* EXPECTED OUTPUT TABLES *********** //
    
    static const int P1_COUNT = 17;
    static const int P2_COUNT = 12;
    static const int P3_COUNT = 19;
    static const int YANKEEDOODLE_COUNT = 55;
    
    const int PITCH_STRENGTH_EXPECTED = 0;
    const int IOI_STRENGTH_EXPECTED = 1;
    const int REST_STRENGTH_EXPECTED = 2;
    const int WEIGHTED_AVG_STRENGTH_EXPECTED = 3;
    
    
    float strength_P1_expected[P1_COUNT][4] =
    {
        //	PITCH               IOI                 REST			WEIGHTED AVG
        {5184.00000,		65536.00000,		0.0000,			17032.00000},		// 0
        {0.00000,			0.00000,			0.0000,			0.00000},			// 1
        {0.00000,			0.00000,			0.0000,			0.00000},			// 2
        {0.00000,			85.33334,			0.0000,			21.33333},			// 3
        {0.00000,			170.66667,			0.0000,			42.66667},			// 4
        {0.00000,			170.66667,			0.0000,			42.66667},			// 5
        {0.00000,			1137.77783,			0.0000,			284.44446},			// 6
        {0.00000,			99.55556,			0.0000,			24.88889},			// 7
        {0.00000,			0.00000,			0.0000,			0.00000},			// 8
        {0.00000,			0.00000,			0.0000,			0.00000},			// 9
        {0.00000,			76.80000,			0.0000,			19.20000},			// 10
        {0.00000,			380.34286,			0.0000,			95.08572},			// 11
        {0.00000,			246.85715,			0.0000,			61.71429},			// 12
        {0.00000,			128.00000,			0.0000,			32.00000},			// 13
        {0.00000,			384.00000,			0.0000,			96.00000},			// 14
        {0.00000,			163.55556,			0.0000,			40.88889},			// 15
        {0.00000,			796.44446,			0.0000,			199.11111}          // 16
    };
    
    float strength_P2_expected[P2_COUNT][4] =
    {
        //	PITCH           IOI                 REST			WEIGHTED AVG
        {5184.50391,		262144.00000,		0.0000,			66184.06250},		// 0
        {1.51079,			0.00000,			0.0000,			0.18885},			// 1
        {2.00042,			0.00000,			0.0000,			0.25005},			// 2
        {2.00045,			0.00000,			0.0000,			0.25006},			// 3
        {1.48872,			0.00000,			0.0000,			0.18609},			// 4
        {1.51200,			0.00000,			0.0000,			0.18900},			// 5
        {2.00052,			0.00000,			0.0000,			0.25007},			// 6
        {2.91909,			0.00000,			0.0000,			0.36489},			// 7
        {3.53016,			0.00000,			0.0000,			0.44127},			// 8
        {3.94442,			0.00000,			0.0000,			0.49305},			// 9
        {74.58991,			0.00000,			0.0000,			9.32374},			// 10
        {00.00000,          0.00000,			512.0000,      64.00000},           // 11
    };
    
    float strength_P3_expected[P3_COUNT][4] =
    {
        //	PITCH               IOI                 REST                WEIGHTED AVG
        {2307.26221,		65536.00000,		0.00000,			16672.40820},			// 0
        {5.27992,			0.00000,			0.00000,			0.65999},               // 1
        {3.53794,			0.00000,			0.00000,			0.44224},               // 2
        {49.92000,			153.60001,			0.00000,			44.64000},              // 3
        {0.00000,           1228.80005,			2048.00000,			563.20001},             // 4
        {49.92000,			153.60001,			0.00000,			44.64000},              // 5
        {3.53794,			0.00000,			0.00000,			0.44224},               // 6
        {3.93336,			0.00000,			0.00000,			0.49167},               // 7
        {5.21739,			0.00000,			0.00000,			0.65217},               // 8
        {3.93336,			0.00000,			0.00000,			0.49167},               // 9
        {53.45795,			85.33334,			0.00000,			28.01558},              // 10
        {0.00000,           341.33334,			1024.00000,			213.33334},             // 11
        {120.00000,			85.33334,			0.00000,			36.33334},              // 12
        {0.00000,           0.00000,			512.00000,			64.00000},              // 13
        {110.00000,			0.00000,			0.00000,			13.75000},              // 14
        {0.00000,           0.00000,			512.00000,			64.00000},              // 15
        {104.00000,			0.00000,			0.00000,			13.00000},              // 16
        {0.00000,           85.33334,			512.00000,			85.33334},              // 17
        {48.00000,			170.66667,			0.00000,			48.66667},              // 18
    };
    
    float strength_YD_expected[YANKEEDOODLE_COUNT][4] =
    {
        //	PITCH               IOI                 REST			WEIGHTED AVG
        {4489.00000,		16384.00000,		0.0000,			4657.12500},		// 0
        {0.98529,			0.00000,			0.0000,			0.12316},			// 1
        {2.00042,			0.00000,			0.0000,			0.25005},			// 2
        {3.07226,			0.00000,			0.0000,			0.38403},			// 3
        {3.88406,			0.00000,			0.0000,			0.48551},			// 4
        {3.07226,			0.00000,			0.0000,			0.38403},			// 5
        {4.67274,			0.00000,			0.0000,			0.58409},			// 6
        {5.71608,			0.00000,			0.0000,			0.71451},			// 7
        {2.59690,			0.00000,			0.0000,			0.32461},			// 8
        {0.98529,			0.00000,			0.0000,			0.12316},			// 9
        {2.00042,			0.00000,			0.0000,			0.25005},			// 10
        {3.07226,			42.66667,			0.0000,			11.05070},			// 11
        {2.44579,			85.33334,			0.0000,			21.63906},			// 12
        {0.99248,			85.33334,			0.0000,			21.45739},			// 13
        {0.50376,			42.66667,			0.0000,			10.72964},			// 14
        {0.98529,			0.00000,			0.0000,			0.12316},			// 15
        {2.00042,			0.00000,			0.0000,			0.25005},			// 16
        {1.51079,			0.00000,			0.0000,			0.18885},			// 17
        {1.00699,			0.00000,			0.0000,			0.12587},			// 18
        {1.51079,			0.00000,			0.0000,			0.18885},			// 19
        {2.00042,			0.00000,			0.0000,			0.25005},			// 20
        {1.48905,			0.00000,			0.0000,			0.18613},			// 21
        {2.55874,			0.00000,			0.0000,			0.31984},			// 22
        {2.92163,			0.00000,			0.0000,			0.36520},			// 23
        {2.00049,			0.00000,			0.0000,			0.25006},			// 24
        {1.51163,			42.66667,			0.0000,			10.85562},			// 25
        {0.50376,			85.33334,			0.0000,			21.39630},			// 26
        {1.53435,			36.57143,			0.0000,			9.33465},			// 27
        {2.45026,			123.42857,			0.0000,			31.16343},			// 28
        {2.03077,			53.33334,			0.0000,			13.58718},			// 29
        {2.00049,			42.66667,			0.0000,			10.91673},			// 30
        {1.96825,			0.00000,			0.0000,			0.24603},			// 31
        {2.00049,			0.00000,			0.0000,			0.25006},			// 32
        {1.51163,			42.66667,			0.0000,			10.85562},			// 33
        {3.10066,			121.90477,			0.0000,			30.86378},			// 34
        {3.38723,			123.42857,			0.0000,			31.28055},			// 35
        {2.03175,			53.33334,			0.0000,			13.58730},			// 36
        {2.00052,			42.66667,			0.0000,			10.91673},			// 37
        {1.48781,			42.66667,			0.0000,			10.85264},			// 38
        {1.95861,			85.33334,			0.0000,			21.57816},			// 39
        {2.52132,			36.57143,			0.0000,			9.45802},			// 40
        {2.00049,			123.42857,			0.0000,			31.10720},			// 41
        {2.03077,			53.33334,			0.0000,			13.58718},			// 42
        {2.00049,			42.66667,			0.0000,			10.91673},			// 43
        {1.96825,			0.00000,			0.0000,			0.24603},			// 44
        {2.00049,			0.00000,			0.0000,			0.25006},			// 45
        {1.51163,			0.00000,			0.0000,			0.18895},			// 46
        {2.03811,			0.00000,			0.0000,			0.25476},			// 47
        {2.48152,			0.00000,			0.0000,			0.31019},			// 48
        {3.38723,			0.00000,			0.0000,			0.42340},			// 49
        {3.10066,			0.00000,			0.0000,			0.38758},			// 50
        {1.96291,			0.00000,			0.0000,			0.24536},			// 51
        {2.54804,			42.66667,			0.0000,			10.98517},			// 52
        {0.98529,			85.33334,			0.0000,			21.45650},			// 53
        {0.00000,			0.00000,			0.0000,			0.00000}			// 54
    };
    
    
    const int START_MEASURE_EXPECTED = 0;
    const int START_INDEX_EXPECTED = 1;
    const int START_PITCH_EXPECTED = 2;
    const int START_DURATION_EXPECTED = 3;

    const int END_MEASURE_EXPECTED = 4;
    const int END_INDEX_EXPECTED = 5;
    const int END_PITCH_EXPECTED = 6;
    const int END_DURATION_EXPECTED = 7;

    float notes_YD_expected[YANKEEDOODLE_COUNT][8] =
    {
    //  START_MEASURE, START_INDEX, START_PITCH, START_DURATION, END_MEASURE, END_INDEX,  END_PITCH,  END_DURATION
        {0,0,   0,     0,               1,1,    67  ,    128},
        {1,1,   67,	 128,               1,2	,	67	,	 128},
        {1,2,   67,	 128,               1,3	,	69	,	 128},
        {1,3,   69,	 128,	            1,4	,	71	,	 128},
        {1,4,   71,	 128,	            1,5	,	67	,	 128},
        {1,5,	67,	 128,	            1,6	,	71	,	 128},
        {1,6,	71,	 128,	            1,7	,	69	,	 128},
        {1,7,	69,	 128,	            1,8	,	62	,	 128},
        {1,8,	62,	 128,	            2,1	,	67	,	 128},
        {2,1,	67,	 128,	            2,2	,	67	,	 128},
        {2,2,	67,	 128,	            2,3	,	69	,	 128},
        {2,3,	69,	 128,	            2,4	,	71	,	 128},
        {2,4,	71,	 128,	            2,5	,	67	,	 256},
        {2,5,	67,	 256,	            2,6	,	66	,	 256},
        {2,6,	66,	 256,	            3,1	,	67	,	 128},
        {3,1,	67,	 128,	            3,2	,	67	,	 128},
        {3,2,	67,	 128,	            3,3	,	69	,	 128},
        {3,3,	69,	 128,	            3,4	,	71	,	 128},
        {3,4,	71,	 128,	            3,5	,	72	,	 128},
        {3,5,	72,	 128,	            3,6	,	71	,	 128},
        {3,6,	71,	 128,	            3,7	,	69	,	 128},
        {3,7,	69,	 128,	            3,8	,	67	,	 128},
        {3,8,	67,	 128,	            4,1	,	66	,	 128},
        {4,1,	66,	 128,	            4,2	,	62	,	 128},
        {4,2,	62,	 128,	            4,3	,	64	,	 128},
        {4,3,	64,	 128,	            4,4	,	66	,	 128},
        {4,4,	66,	 128,	            4,5	,	67	,	 256},
        {4,5,	67,	 256,	            4,6	,	67	,	 256},
        {4,6,	67,	 256,	            5,1	,	64	,	 192},
        {5,1,	64,	 192,	            5,2	,	66	,	 64},
        {5,2,	66,	 64,	            5,3	,	64	,	 128},
        {5,3,	64,	 128,	            5,4	,	62	,	 128},
        {5,4,	62,	 128,	            5,5	,	64	,	 128},
        {5,5,	64,	 128,	            5,6	,	66	,	 128},
        {5,6,	66,	 128,	            5,7	,	67	,	 256},
        {5,7,	67,	 256,	            6,1	,	62	,	 192},
        {6,1,	62,	 192,	            6,2	,	64	,	 64},
        {6,2,	64,	 64,		        6,3	,	62	,	 128},
        {6,3,	62,	 128,	            6,4	,	60	,	 128},
        {6,4,	60,	 128,	            6,5	,	59	,	 256},
        {6,5,	59,	 256,	            6,6	,	62	,	 256},
        {6,6,	62,	 256,	            7,1	,	64	,	 192},
        {7,1,	64,	 192,	            7,2	,	66	,	 64},
        {7,2,	66,	 64,	            7,3	,	64	,	 128},
        {7,3,	64,	 128,	            7,4	,	62	,	 128},
        {7,4,	62,	 128,	            7,5	,	64	,	 128},
        {7,5,	64,	 128,	            7,6	,	66	,	 128},
        {7,6,	66,	 128,	            7,7	,	67	,	 128},
        {7,7,	67,	 128,	            7,8	,	64	,	 128},
        {7,8,	64,	 128,	            8,1	,	62	,	 128},
        {8,1,	62,	 128,	            8,2	,	67	,	 128},
        {8,2,	67,	 128,	            8,3	,	66	,	 128},
        {8,3,	66,	 128,	            8,4	,	69	,	 128},
        {8,4,	69,	 128,	            8,5	,	67	,	 256},
        {8,5,	67,	 256,	            8,6	,	67	,	 256}
    };
    
};


#endif
