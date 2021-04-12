// Copyright (c) 2018 Microsoft Corporation
// Licensed under the MIT license.
// Author: Paul Koch <code@koch.ninja>

#ifndef REGISTRATION_EXCEPTIONS_H
#define REGISTRATION_EXCEPTIONS_H

#include <exception>

#include "ebm_native.h"
#include "zones.h"

namespace DEFINED_ZONE_NAME {
#ifndef DEFINED_ZONE_NAME
#error DEFINED_ZONE_NAME must be defined
#endif // DEFINED_ZONE_NAME

class SkipRegistrationException final : public std::exception {
public:
   SkipRegistrationException() = default;
};

class ParameterValueOutOfRangeException final : public std::exception {
public:
   ParameterValueOutOfRangeException() = default;
};

class ParameterMismatchWithConfigException final : public std::exception {
public:
   ParameterMismatchWithConfigException() = default;
};

class ParameterValueMalformedException final : public std::exception {
   // this should not be thrown from the Registrable constructor
public:
   ParameterValueMalformedException() = default;
};

class ParameterUnknownException final : public std::exception {
   // this should not be thrown from the Registrable constructor
public:
   ParameterUnknownException() = default;
};

class RegistrationConstructorException final : public std::exception {
   // this should not be thrown from the Registrable constructor
public:
   RegistrationConstructorException() = default;
};

class IllegalParamNameException final : public std::exception {
   // this should not be thrown from the Registrable constructor
public:
   IllegalParamNameException() = default;
};

class IllegalRegistrationNameException final : public std::exception {
   // this should not be thrown from the Registrable constructor
public:
   IllegalRegistrationNameException() = default;
};

class DuplicateParamNameException final : public std::exception {
   // this should not be thrown from the Registrable constructor
public:
   DuplicateParamNameException() = default;
};

} // DEFINED_ZONE_NAME

#endif // REGISTRATION_EXCEPTIONS_H
