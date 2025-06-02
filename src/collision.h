#pragma once
#include "world.h"

void CreateContacts(const bodies_t& bodies, contacts_t& contacts);

void SeparateContacts(contacts_t& contacts);

void ResolveContacts(contacts_t& contacts);