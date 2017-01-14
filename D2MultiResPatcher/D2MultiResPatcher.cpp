// D2MultiResPatcher.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "detourshelper.h"

static const u32 g_D2ClientImageBase = 0x6FAB0000;
static const u32 g_D2gfxImageBase = 0x6FA80000;
static const u32 g_D2GdiImageBase = 0x6F870000;
static const u32 g_D2CommonImageBase = 0x6FD50000;
static const u32 g_D2Direct3DImageBase = 0x6F880000;
static const u32 g_D2DDrawImageBase = 0x6F8C0000;

struct AddrNeedToPatch
{
	const char *dll;
	u32 offset;
	u32 orig_image_base;
};

static const AddrNeedToPatch g_AddrNeedToPatch[] =
{
	{ "D2Client.dll", 0x10E00, g_D2ClientImageBase },
	{ "D2Client.dll", 0x10E05, g_D2ClientImageBase },
	{ "D2Client.dll", 0x10E0C, g_D2ClientImageBase },
	{ "D2Client.dll", 0x10E11, g_D2ClientImageBase },
	{ "D2Client.dll", 0x10E17, g_D2ClientImageBase },
	{ "D2Client.dll", 0x143BD, g_D2ClientImageBase },
	{ "D2Client.dll", 0x272AB, g_D2ClientImageBase },
	{ "D2Client.dll", 0x29268, g_D2ClientImageBase },
	{ "D2Client.dll", 0x2926F, g_D2ClientImageBase },
	{ "D2Client.dll", 0x37D63, g_D2ClientImageBase },
	{ "D2Client.dll", 0x662A2, g_D2ClientImageBase },
	{ "D2Client.dll", 0xC39F2, g_D2ClientImageBase },
	{ "D2Client.dll", 0xC39F7, g_D2ClientImageBase },
	{ "D2Client.dll", 0xC39FD, g_D2ClientImageBase },
	{ "D2Client.dll", 0xCDE02, g_D2ClientImageBase },
	{ "D2Client.dll", 0xCDE33, g_D2ClientImageBase },
	{ "D2Client.dll", 0xCDE52, g_D2ClientImageBase },
	{ "D2Client.dll", 0xCDE60, g_D2ClientImageBase },
	{ "D2Client.dll", 0xCDE91, g_D2ClientImageBase },
	{ "D2Client.dll", 0xCDEA2, g_D2ClientImageBase },

	{ "D2gfx.dll", 0x7FE2, g_D2gfxImageBase },
	{ "D2gfx.dll", 0x7FEB, g_D2gfxImageBase },
	{ "D2gfx.dll", 0xCC52, g_D2gfxImageBase },
	{ "D2gfx.dll", 0xCC62, g_D2gfxImageBase },
	{ "D2gfx.dll", 0xCC72, g_D2gfxImageBase },
	{ "D2gfx.dll", 0xCC82, g_D2gfxImageBase },
	{ "D2gfx.dll", 0xCC92, g_D2gfxImageBase },
	{ "D2gfx.dll", 0xCCA2, g_D2gfxImageBase },
	{ "D2gfx.dll", 0xCCAA, g_D2gfxImageBase },


	{ "D2Gdi.dll", 0x6D38, g_D2GdiImageBase },
	{ "D2Gdi.dll", 0x6D40, g_D2GdiImageBase },
	{ "D2Gdi.dll", 0x703E, g_D2GdiImageBase },
	{ "D2Gdi.dll", 0x7045, g_D2GdiImageBase },
	{ "D2Gdi.dll", 0x704A, g_D2GdiImageBase },
	{ "D2Gdi.dll", 0x7135, g_D2GdiImageBase },
	{ "D2Gdi.dll", 0x713B, g_D2GdiImageBase },
	{ "D2Gdi.dll", 0x7142, g_D2GdiImageBase },
	{ "D2Gdi.dll", 0x7147, g_D2GdiImageBase },

	{ "D2Common.dll", 0x887E6, g_D2CommonImageBase },
	{ "D2Common.dll", 0x88806, g_D2CommonImageBase },
	{ "D2Common.dll", 0x88826, g_D2CommonImageBase },
	{ "D2Common.dll", 0x88846, g_D2CommonImageBase },
	{ "D2Common.dll", 0x88866, g_D2CommonImageBase },

	{ "D2Direct3D.dll", 0xB99E, g_D2Direct3DImageBase },
	{ "D2Direct3D.dll", 0xB9A6, g_D2Direct3DImageBase },
	{ "D2Direct3D.dll", 0xB9AB, g_D2Direct3DImageBase },
	{ "D2Direct3D.dll", 0xB9B1, g_D2Direct3DImageBase },
	{ "D2Direct3D.dll", 0xB9B6, g_D2Direct3DImageBase },

	{ "D2DDraw.dll", 0x85C7, g_D2DDrawImageBase },
	{ "D2DDraw.dll", 0x85CF, g_D2DDrawImageBase },
	{ "D2DDraw.dll", 0x85D4, g_D2DDrawImageBase },
	{ "D2DDraw.dll", 0x85DF, g_D2DDrawImageBase },
	{ "D2DDraw.dll", 0x85E5, g_D2DDrawImageBase },
	{ "D2DDraw.dll", 0x85EA, g_D2DDrawImageBase },
	{ "D2DDraw.dll", 0x85F0, g_D2DDrawImageBase },
};

static void PatchAddr(const AddrNeedToPatch& patch)
{
	u32 cur_base = (u32)GetModuleHandle(patch.dll);
	u32 addr = patch.offset + cur_base;

	u32 wrong_addr = *(u32 *)addr;
	u32 delta = wrong_addr - patch.orig_image_base;
	u32 right_addr = delta + cur_base;

	CDetourEnableWriteOnCodePage hlp((PBYTE)addr);
	*(u32 *)addr = right_addr;
}

void PatchIt()
{
	for (const auto& addr : g_AddrNeedToPatch)
		PatchAddr(addr);
}
