#pragma once

#include <stdio.h>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#define LOG(X, ...) printf(X "\n", __VA_ARGS__)

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using WeakRef = std::weak_ptr<T>;

template<typename T>
using Vector = std::vector<T>;

template<typename Key, typename Value>
using Map = std::map<Key, Value>;

template<typename Key, typename Value, typename Hasher = std::hash<Key>>
using Dict = std::unordered_map<Key, Value, Hasher>;

template<typename Key>
using Set = std::unordered_set<Key>;