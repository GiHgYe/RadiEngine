#include "cursor.h"

Cursor::Cursor(const CXCursor& handle) : m_handle(handle) {}

CXCursorKind Cursor::GetKind(void) const { return clang_getCursorKind(m_handle); }

std::string Cursor::GetSpelling(void) const { return Utils::toString(clang_getCursorSpelling(m_handle)); }

std::string Cursor::GetDisplayName(void) const { return Utils::toString(clang_getCursorDisplayName(m_handle)); }

std::string Cursor::GetSourceFile(void) const
{
	auto range = clang_Cursor_getSpellingNameRange(m_handle, 0, 0);
	auto start = clang_getRangeStart(range);

	CXFile   file;
	unsigned line, column, offset;

	clang_getFileLocation(start, &file, &line, &column, &offset);
	return Utils::toString(clang_getFileName(file));
}

bool Cursor::isDefinition(void) const { return clang_isCursorDefinition(m_handle) ? true : false; }

CursorType Cursor::GetType(void) const { return clang_getCursorType(m_handle); }

Cursor::List Cursor::GetChildren(void) const
{
	List container;

	Visitor visitor = [](CXCursor cursor, CXCursor parent, CXClientData data) {
		auto list = static_cast<List*>(data);
		list->emplace_back(cursor);

		if (cursor.kind == CXCursor_LastPreprocessing)
			return CXChildVisit_Break;

		return CXChildVisit_Continue;
	};
	clang_visitChildren(m_handle, visitor, &container);

	return container;
}

void Cursor::VisitChildren(Visitor visitor, void* data) { clang_visitChildren(m_handle, visitor, data); }


