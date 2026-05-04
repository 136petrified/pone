/*    Created:    2025-10-17
 *    Modified:   2026-05-04
 */

#pragma once

#include <godot-cpp/classes/sprite2d.hpp>

namespace godot {

class GodotPone : public Sprite2D {
    GDCLASS(GodotPone, Sprite2D)

  private:
    double m_timePassed;

  protected:
    static void _bind_methods();

  public:
    GodotPone();
    ~GodotPone();

    void _process(double delta) override;
};

} // namespace godot
