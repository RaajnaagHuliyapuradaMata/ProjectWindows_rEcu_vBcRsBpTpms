

#ifndef _CAN_TABLE_H_
#define _CAN_TABLE_H_

#include "Types.h"

#define RX_RULE_NUM_MAX              (192U)
#define RX_RULE_PAGE_NUM             (1U)

#define RX_RULE_NUM                  (12U)
#define RX_RULE_NUM_CH0              (11U)
#define RX_RULE_NUM_CH1              (0U)
#define RX_RULE_NUM_CH2              (0U)
#define RX_RULE_NUM_CH3              (0U)
#define RX_RULE_NUM_CH4              (0U)

typedef struct {
  uint32 lword[4];
}can_cre_type;

extern const can_cre_type RX_RULE_TABLE_LIST[RX_RULE_NUM];
#endif
