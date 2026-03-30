/*    Created:    2025-10-17
 *    Modified:   2026-03-03
 */

#include "pone.hpp"

using namespace godot;

void GodotPone::_bind_methods() {}

GodotPone::GD_Pone() : m_timePassed{0.0} {}

GodotPone::~GodotPone() {}

void GodotPone::_process(double delta) {
    m_timePassed += delta;
}
