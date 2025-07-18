#
# Quake2 gamei386.real.so Makefile for Linux
#
# Jan '98 by Zoid <zoid@idsoftware.com>
#
# ELF only
#
# Edited December 08, 2018 by QwazyWabbit
#

.DEFAULT_GOAL := game

# this nice line comes from the linux kernel makefile
ARCH := $(shell uname -m | sed -e s/i.86/i386/ \
	-e s/sun4u/sparc64/ -e s/arm.*/arm/ \
	-e s/sa110/arm/ -e s/alpha/axp/)

# On 64-bit OS use the command: setarch i386 make all
# to obtain the 32-bit binary DLL on 64-bit Linux.

CC = clang -std=c17 -Wpedantic -Wall

# on x64 machines do this preparation:
# sudo apt-get install ia32-libs
# sudo apt-get install libc6-dev-i386
# On Ubuntu 16.x and higher use sudo apt install libc6-dev-i386
# this will let you build 32-bits on ia64 systems
#
# This is for native build
CFLAGS=-O3 -DARCH="$(ARCH)" -DSTDC_HEADERS
# This is for 32-bit build on 64-bit host
ifeq ($(ARCH),i386)
CFLAGS =-m32 -O3 -DARCH="$(ARCH)" -DSTDC_HEADERS -I/usr/include
endif

# use this when debugging
#CFLAGS=-g -Og -DDEBUG -DARCH="$(ARCH)" -Wall -pedantic

# flavors of Linux
ifeq ($(shell uname),Linux)
CFLAGS += -DLINUX
LIBTOOL = ldd
endif

# OS X wants to be Linux and FreeBSD too.
ifeq ($(shell uname),Darwin)
CFLAGS += -DLINUX
LIBTOOL = otool
endif

SHLIBEXT=so
#set position independent code
SHLIBCFLAGS=-fPIC

# Build directory
BUILD_DIR = build$(ARCH)
# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
DO_SHLIB_CC=$(CC) $(CFLAGS) $(SHLIBCFLAGS) -o $@ -c $<

# Pattern rule to place objects in build directory
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(DO_SHLIB_CC)

#############################################################################
# SETUP AND BUILD
# GAME
#############################################################################

GAME_SRCS = \
flashlight.c g_ai.c g_chase.c g_cmds.c g_combat.c g_func.c g_main.c g_misc.c \
g_monster.c g_newai.c g_newdm.c g_newfnc.c g_newtarg.c g_newtrig.c g_newweap.c \
g_phys.c g_save.c g_spawn.c g_svcmds.c g_target.c g_trigger.c g_turret.c g_utils.c \
g_weapon.c m_actor.c m_berserk.c m_boss2.c m_boss3.c m_boss31.c m_boss32.c \
m_brain.c m_chick.c m_flash.c m_flipper.c m_float.c m_flyer.c m_gladiator.c \
m_gunner.c m_hover.c m_infantry.c m_insane.c m_medic.c m_move.c m_mutant.c \
m_parasite.c m_soldier.c m_supertank.c m_tank.c p_client.c p_hud.c p_trail.c \
p_view.c q_shared.c z_arifle.c z_armour.c z_bitchrl.c z_chaingun.c z_client.c \
z_cmds.c z_coop.c z_glauncher.c z_gunnercg.c z_handgrenade.c z_hands.c z_health.c \
z_infweapon.c z_items.c z_medichb.c z_pistol.c z_railgun.c z_shotgun.c z_submach.c \
z_sweapon.c z_tankrl.c z_weapon.c z_wedit.c

GAME_OBJS = $(GAME_SRCS:%.c=$(BUILD_DIR)/%.o)

# Build all object files that are out-of-date
game: $(GAME_OBJS) game$(ARCH).real.$(SHLIBEXT)
# Build everything (always rebuild all objects and the shared library)

all: 
	$(MAKE) clean
	$(MAKE) $(BUILD_DIR) $(GAME_OBJS) game$(ARCH).real.$(SHLIBEXT)

# Main target: depends on all object files
game$(ARCH).real.$(SHLIBEXT) : $(GAME_OBJS)
	$(CC) $(CFLAGS) -shared -o $@ $(GAME_OBJS) -ldl -lm
	$(LIBTOOL) -r $@
	file $@

#############################################################################
# MISC
#############################################################################

clean:
	rm -rf $(BUILD_DIR)

depends:
	$(CC) $(CFLAGS) -MM $(GAME_SRCS) > dependencies

-include dependencies

