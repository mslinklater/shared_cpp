// Copyright (c) 2019, Martin Linklater
// All rights reserved.
//
// See file 'LICENSE' for license details

#pragma once

enum eErrorCode {
	kError_OK = 0,
	kError_CommandLineParsing,
	kError_MemoryAlreadyInitialised,
	kError_MemoryNotInitialised,
	kError_FileNotFound,
	kError_JSONParse
};
