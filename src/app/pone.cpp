/*    Created:    10-17-2025
 *    Modified:   10-17-2025
 */

#include "pone.hpp"

using namespace godot;

void GD_Pone::_bind_methods() {}

GD_Pone::GD_Pone() : m_timePassed{0.0} {}

GD_Pone::~GD_Pone() {}

void GD_Pone::_process(double delta) {
    m_timePassed += delta;
}
