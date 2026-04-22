//
// Public declarations of flashlight functions
//
#pragma once

void Cmd_Flashlight(edict_t* ent);
void FlashlightReset(edict_t* self);
void Use_Flashlight (edict_t *player);
void flashlight_think (edict_t *self);

extern	cvar_t* flashlightmode;

/* Add these to g_client_s struct
edict_t* flashlight;
int		flashtype;
*/
