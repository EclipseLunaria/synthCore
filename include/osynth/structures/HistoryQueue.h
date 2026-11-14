#pragma once
#include <array>
#include <concepts>
#include <cstddef>
#include <optional>

namespace OSynth::Core::Structures {
    template <typename T, size_t Capacity>
    class HistoryQueue{
        // Static Asserts
        static_assert(std::is_trivially_copyable<T>());
        struct Node {
            Node(): value(std::nullopt), active(false), next(nullptr), prev(nullptr) {}

            std::optional<T> value = std::nullopt;
            bool active = false;
            Node * next = nullptr;
            Node * prev = nullptr;
            
            void reset(){
                next = nullptr;
                prev = nullptr;
                active = false;
            }
        };

        public:
        HistoryQueue(){
            for (int i = 0; i < Capacity; i++){
                m_slots[i] = Node();
            }
        }

        bool press(T v){
            for (int i = 0; i < Capacity; i++){
                Node * n = &m_slots[i];
                //std::cout << "Node index: " << i << std::endl;
                if (n->active == false){
                    n->active = true;
                    n->prev = nullptr;
                    n->value = v;
                    n->next = m_head;
                    if (m_head != nullptr){
                        m_head->prev = n;
                    }

                    m_head = n;
                    m_size++;
                    return true;
                }
                if (n->value == v){
                    return false;
                }
            }
            return false;
        }

        bool release(T v){
            // find the node
            Node * node = nullptr;
            for (int i = 0; i < Capacity; i++){
                Node * current = &m_slots[i];
                if (current->active && current->value == v){
                    node = current;
                }
            }
            if (node == nullptr){
                return false;
            }
            // case were T is the head
            else if (node == m_head){
                m_head = m_head->next;
            }
            else {
                node->prev->next = node->next;
            }

            node->reset();
            m_size--;
            return true;
        }

        bool check(T v){
            return find(v) != nullptr;
        }

        T * const most_recent(){
            if (m_head == nullptr) return nullptr;

            return &m_head->value.value();
        }

        size_t view_history(T ** buffer){
            Node * current = m_head;
            size_t n = 0;
            while (current){
                T * value_ptr = &current->value.value();
                buffer[n] = value_ptr;
                n++;
                current = current->next;
            }
            return n;
        }

        size_t size() const{
            return m_size;
        }

        size_t capacity() const {
            return Capacity;
        }

        private:
        Node * m_head = nullptr;
        size_t m_size = 0;
        Node m_slots[Capacity];


        Node * const find(T v){
            for (int i = 0; i < Capacity; i++){
                if (!m_slots->active) continue;

                if (m_slots->value.value() == v) return &m_slots[i];
            }
            return nullptr;
        }
        
    };
}