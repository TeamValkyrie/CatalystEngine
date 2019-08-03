#pragma once

#include "Engine/Subsystem/Subsystem.h"

#include "imgui.h"

#include <vector>
#include <ctype.h>

class Console : public Subsystem
{

public:

	Console();
	virtual ~Console();

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Deinit() override;

	void ClearLog();
	void AddLog(const char* Log, ...) IM_FMTARGS(2);
	void Draw(const char* Title, bool* bShow);

private:

	void ExecuteCommand(char* Command);

	static int   Stricmp(const char* str1, const char* str2) { int d; while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
	static int   Strnicmp(const char* str1, const char* str2, int n) { int d = 0; while (n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; n--; } return d; }
	static char* Strdup(const char* str) { size_t len = strlen(str) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)str, len); }
	static void  Strtrim(char* str) { char* str_end = str + strlen(str); while (str_end > str && str_end[-1] == ' ') str_end--; *str_end = 0; }

private:


	char InputBuf[256];
	std::vector<char*> m_Entries;
	std::vector<const char*> m_Commands;
	std::vector<char*> m_History;

	int m_HistoryPos;
	ImGuiTextFilter m_Filter;
	bool m_bAutoScroll;
	bool m_bScrollToBottom;

};