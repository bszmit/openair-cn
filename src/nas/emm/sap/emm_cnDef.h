/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under 
 * the Apache License, Version 2.0  (the "License"); you may not use this file
 * except in compliance with the License.  
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

/*****************************************************************************

Source      emm_cnDef.h

Version     0.1

Date        2013/12/05

Product     NAS stack

Subsystem   EPS Core Network

Author      Sebastien Roux, Lionel GAUTHIER

Description

*****************************************************************************/


#ifndef FILE_EMM_CNDEF_SEEN
#define FILE_EMM_CNDEF_SEEN
#include "intertask_interface.h"
#include "emm_proc.h"

typedef enum emmcn_primitive_s {
  _EMMCN_START = 400,
  _EMMCN_AUTHENTICATION_PARAM_RES,
  _EMMCN_AUTHENTICATION_PARAM_FAIL,
  _EMMCN_CONTEXT_RES,
  _EMMCN_CONTEXT_FAIL,
  _EMMCN_DEREGISTER_UE,
  _EMMCN_PDN_CONFIG_RES, // LG
  _EMMCN_PDN_CONFIG_FAIL, // DB
  _EMMCN_PDN_CONNECTIVITY_RES, // LG
  _EMMCN_PDN_CONNECTIVITY_FAIL,// LG
  _EMMCN_PDN_DISCONNECT_RES,// LG
  _EMMCN_ACTIVATE_DEDICATED_BEARER_REQ,// LG
  _EMMCN_DEACTIVATE_DEDICATED_BEARER_REQ,// LG
  _EMMCN_IMPLICIT_DETACH_UE,
  _EMMCN_SMC_PROC_FAIL,
  _EMMCN_END
} emm_cn_primitive_t;

typedef struct emm_cn_auth_res_s {
  /* UE identifier */
  mme_ue_s1ap_id_t ue_id;

  /* For future use: nb of vectors provided */
  uint8_t nb_vectors;

  /* Consider only one E-UTRAN vector for the moment... */
  eutran_vector_t *vector[MAX_EPS_AUTH_VECTORS];
} emm_cn_auth_res_t;

typedef struct emm_cn_auth_fail_s {
  /* UE identifier */
  mme_ue_s1ap_id_t    ue_id;

  /* S6A mapped to NAS cause */
  nas_cause_t cause;
} emm_cn_auth_fail_t;


typedef struct emm_cn_ctx_res_s {
  /* UE identifier */
  mme_ue_s1ap_id_t ue_id;

  uint64_t                imsi;
  imsi_t                  _imsi;

  imei_t                  _imei;

  mm_context_eps_t        mm_eps_context;

} emm_cn_ctx_res_t;

typedef struct emm_cn_context_fail_s {
  /* UE identifier */
  mme_ue_s1ap_id_t    ue_id;

  /* S10 mapped to NAS cause */
  gtpv2c_cause_value_t cause;
} emm_cn_context_fail_t;

struct itti_nas_pdn_config_rsp_s;
struct itti_nas_pdn_connectivity_rsp_s;
struct itti_nas_pdn_connectivity_fail_s;

typedef struct itti_nas_pdn_config_rsp_s        emm_cn_pdn_config_res_t;
typedef struct itti_nas_pdn_config_fail_s       emm_cn_pdn_config_fail_t;
typedef struct itti_nas_pdn_connectivity_rsp_s  emm_cn_pdn_res_t;
typedef struct itti_nas_pdn_connectivity_fail_s emm_cn_pdn_fail_t;
typedef struct itti_nas_pdn_disconnect_rsp_s    emm_cn_pdn_disconnect_res_t;
typedef struct itti_mme_app_activate_bearer_req_s emm_cn_activate_dedicated_bearer_req_t;
typedef struct itti_mme_app_deactivate_bearer_req_s emm_cn_deactivate_dedicated_bearer_req_t;

/** NAS UE context response. */
typedef itti_nas_context_res_t  emm_cn_context_res_t;

typedef struct emm_cn_deregister_ue_s {
  uint32_t ue_id;
} emm_cn_deregister_ue_t;

typedef struct emm_cn_implicit_detach_ue_s {
  uint32_t ue_id;
  nas_cause_t emm_cause;
  emm_proc_detach_type_t detach_type;
} emm_cn_implicit_detach_ue_t;

typedef struct emm_cn_smc_fail_s {
  mme_ue_s1ap_id_t    ue_id;
  nas_cause_t emm_cause;
} emm_cn_smc_fail_t;

typedef struct emm_mme_ul_s {
  emm_cn_primitive_t primitive;
  union {
    emm_cn_auth_res_t       *auth_res;
    emm_cn_auth_fail_t      *auth_fail;

    emm_cn_context_res_t     *context_res;
    emm_cn_context_fail_t    *context_fail;

    emm_cn_deregister_ue_t   deregister;
    emm_cn_pdn_config_res_t  *emm_cn_pdn_config_res;
    emm_cn_pdn_config_fail_t *emm_cn_pdn_config_fail;
    emm_cn_pdn_res_t        *emm_cn_pdn_res;
    emm_cn_pdn_fail_t       *emm_cn_pdn_fail;
    emm_cn_pdn_disconnect_res_t *emm_cn_pdn_disconnect_res;
    emm_cn_activate_dedicated_bearer_req_t *activate_dedicated_bearer_req;
    emm_cn_deactivate_dedicated_bearer_req_t *deactivate_dedicated_bearer_req;
    emm_cn_implicit_detach_ue_t   emm_cn_implicit_detach;
    emm_cn_smc_fail_t        *smc_fail;
  } u;
} emm_cn_t;

#endif /* FILE_EMM_CNDEF_SEEN */
