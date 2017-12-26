//=============================================================================
// Copyright (C) 2011-2017 The pmp-library developers
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//=============================================================================

#include "PointSetViewer.h"

#include <cfloat>
#include <iostream>
#include <sstream>

//=============================================================================

namespace pmp {

//=============================================================================

PointSetViewer::PointSetViewer(const char* title, int width, int height)
    : TrackballViewer(title, width, height)
{
    // setup draw modes
    clearDrawModes();
    addDrawMode("Points");
    setDrawMode("Points");
}

//-----------------------------------------------------------------------------

PointSetViewer::~PointSetViewer()
{
}

//-----------------------------------------------------------------------------

bool PointSetViewer::loadPointSet(const char* filename)
{
    // load mesh
    if (m_pointSet.read(filename))
    {
        // update scene center and bounds
        BoundingBox bb = m_pointSet.bounds();
        setScene(bb.center(), 0.5 * bb.size());

        updatePointSet();

        std::cout << "Load " << filename << ": " << m_pointSet.nVertices()
                  << " vertices" << std::endl;

        m_filename = filename;
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------

void PointSetViewer::updatePointSet()
{
    // update OpenGL buffers
    m_pointSet.updateOpenGLBuffers();
}

//-----------------------------------------------------------------------------

void PointSetViewer::draw(const std::string& drawMode)
{
    m_pointSet.draw(m_projectionMatrix, m_modelviewMatrix, drawMode);
}

//-----------------------------------------------------------------------------
//
void PointSetViewer::keyboard(int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS) // only react on key press events
        return;

    switch (key)
    {
        case GLFW_KEY_BACKSPACE: // reload model
        {
            loadPointSet(m_filename.c_str());
            break;
        }
        default:
        {
            TrackballViewer::keyboard(key, scancode, action, mods);
            break;
        }
    }
}

//=============================================================================
} // namespace pmp
//=============================================================================
