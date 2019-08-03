#include "Console.h"

#include <Bits.h>

Console::Console() : m_HistoryPos(-1),m_bAutoScroll(false), m_bScrollToBottom(false)
{
	memset(InputBuf, 0, sizeof(InputBuf));
}

Console::~Console() 
{
	ClearLog();
	for (size_t i = 0; i < m_History.size(); i++)
	{
		free(m_History[i]);
	}
}

void Console::Init() 
{
	ClearLog();
	
	m_bAutoScroll = true;
	m_bScrollToBottom = false;
	AddLog("Catalyst Console Initialized...");

	Subsystem::Init();
}

void Console::Tick(float) 
{

}

void Console::Deinit() 
{
	ClearLog();

	Subsystem::Deinit();
}

void Console::ClearLog() 
{
	for (size_t i = 0; i < m_Entries.size(); i++)
	{
		free(m_Entries[i]);
	}
	m_Entries.clear();
}

void Console::AddLog(const char* Log, ...) IM_FMTARGS(2) 
{
	char buf[1024];
	va_list args;
	va_start(args, Log);
	vsnprintf(buf, IM_ARRAYSIZE(buf), Log, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);
	m_Entries.push_back(Strdup(buf));
}

void Console::Draw(const char* Title, bool* bShow) 
{
	if (*bShow) 
	{
		ImGui::SetNextWindowSize(ImVec2(520, 200), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin(Title, bShow))
		{
			ImGui::End();
			return;
		}


		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Close Console"))
			{
				*bShow = false;
			}
			ImGui::EndPopup();
		}

		// Options menu
		if (ImGui::BeginPopup("Options"))
		{
			ImGui::Checkbox("Auto-scroll", &m_bAutoScroll);
			ImGui::EndPopup();
		}

		// Options, Filter
		if (ImGui::Button("Options"))
			ImGui::OpenPopup("Options");
		ImGui::SameLine();
		m_Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
		ImGui::Separator();

		const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
		ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::Selectable("Clear")) ClearLog();
			ImGui::EndPopup();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
		for (int i = 0; i < m_Entries.size(); i++)
		{
			const char* item = m_Entries[i];
			if (!m_Filter.PassFilter(item))
				continue;

			// Normally you would store more information in your item (e.g. make Items[] an array of structure, store color/type etc.)
			bool pop_color = false;
			if (strstr(item, "[error]")) { ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f)); pop_color = true; }
			else if (strncmp(item, "# ", 2) == 0) { ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.6f, 1.0f)); pop_color = true; }
			ImGui::TextUnformatted(item);
			if (pop_color)
				ImGui::PopStyleColor();
		}

		if (m_bScrollToBottom || (m_bAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
			ImGui::SetScrollHereY(1.0f);
		m_bScrollToBottom = false;

		ImGui::PopStyleVar();
		ImGui::EndChild();
		ImGui::Separator();

		// Command-line
		bool reclaim_focus = false;
		if (ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue, 0, (void*)this))
		{
			char* s = InputBuf;
			Strtrim(s);
			if (s[0])
				ExecuteCommand(s);
			strcpy(s, "");
			reclaim_focus = true;
		}


		ImGui::End();
	}
}

Command<int, char* []>* Console::CreateCommand(const char* CommandTitle)
{
	for (auto ExistingCommand : m_Commands) 
	{
		if (ExistingCommand->GetCommandName() == CommandTitle)
		{
			return ExistingCommand;
		}
	}
	Command<int, char*[]>* NewCommand = new Command<int, char*[]>();
	NewCommand->SetCommandName(CommandTitle);
	m_Commands.push_back(NewCommand);
	return NewCommand;
}

void Console::ExecuteCommand(char* Command)
{
	for (size_t i = 0; i < m_Commands.size(); i++)
	{
		if (*m_Commands[i]->GetCommandName() == *Command)
		{
			m_Commands[i]->Dispatch(0, nullptr);
		}
	}
}
