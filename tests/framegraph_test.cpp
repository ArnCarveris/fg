#include "catch.hpp"

#include <fg/framegraph.hpp>
#include <fg/resource_registry.hpp>
#include <gl/buffer.hpp>
#include <gl/texture.hpp>

namespace glr
{
struct buffer : fg::resource<gl::buffer>
{
  void actualize() override
  {
    actual_.emplace();
    actual_->set_data_immutable(static_cast<GLsizeiptr>(size));
  }

  std::size_t size;
};

template<GLenum target>
struct texture : fg::resource<gl::texture<target>>
{
  void actualize() override
  {
    auto& actual = fg::resource<gl::texture<target>>::actual_;
    actual.emplace();
    if      (target == GL_TEXTURE_1D) actual->set_storage(static_cast<GLsizei>(levels), format, static_cast<GLsizei>(size[0]));
    else if (target == GL_TEXTURE_2D) actual->set_storage(static_cast<GLsizei>(levels), format, static_cast<GLsizei>(size[0]), static_cast<GLsizei>(size[1]));
    else if (target == GL_TEXTURE_3D) actual->set_storage(static_cast<GLsizei>(levels), format, static_cast<GLsizei>(size[0]), static_cast<GLsizei>(size[1]), static_cast<GLsizei>(size[2]));
  }

  std::size_t                levels;
  GLenum                     format;
  std::array<std::size_t, 3> size  ;
};
}

TEST_CASE("Framegraph test.", "[framegraph]")
{
  fg::resource_registry<
    glr::buffer, 
    glr::texture<GL_TEXTURE_1D>,
    glr::texture<GL_TEXTURE_2D>,
    glr::texture<GL_TEXTURE_3D>> registry  ;
  auto& buffers    = registry.get<glr::buffer>();
  auto& texture1ds = registry.get<glr::texture<GL_TEXTURE_1D>>();
  auto& texture2ds = registry.get<glr::texture<GL_TEXTURE_2D>>();
  auto& texture3ds = registry.get<glr::texture<GL_TEXTURE_3D>>();

  fg::framegraph framegraph;
}