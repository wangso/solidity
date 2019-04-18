/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * Dialects for Wasm.
 */

#include <libyul/backends/wasm/WasmDialect.h>

using namespace std;
using namespace yul;

WasmDialect::WasmDialect():
	Dialect{AsmFlavour::Strict}
{
	for (auto const& name: {
		"add",
		"sub",
		"mul",
		"div_u",
		"rem_u",
		"and",
		"or",
		"xor",
		"shl",
		"shr_u",
		"eq",
		"ne",
		"lt_u",
		"gt_u",
		"le_u",
		"ge_u"
	})
		addFunction(name, 2, 1);

	addFunction("eqz", 1, 1);
	addFunction("drop", 1, 0);
	addFunction("store", 2, 0);
	addFunction("load", 1, 1);
	addFunction("unreachable", 0, 0);
}

BuiltinFunction const* WasmDialect::builtin(YulString _name) const
{
	auto it = m_functions.find(_name);
	if (it != m_functions.end())
		return &it->second;
	else
		return nullptr;
}

void WasmDialect::addFunction(string _name, size_t _params, size_t _returns)
{
	YulString name{std::move(_name)};
	BuiltinFunction& f = m_functions[name];
	f.name = name;
	f.parameters.resize(_params);
	f.returns.resize(_returns);
	f.movable = false;
	f.literalArguments = false;
}
