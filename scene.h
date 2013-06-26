////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2013 the Good Evil GmbH
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <sifteo.h>

namespace sappy {

class Cube;

class Scene {
  private:
    friend class Cube;

    bool load(Sifteo::AssetLoader* loader, Sifteo::CubeID cid, Sifteo::VideoBuffer& vbuf);

    virtual void onPaint(Cube& cube) {}
    virtual void onIdle(Cube& cube) {}
    virtual void onTouch(Cube& cube) {}

    virtual bool onNeighborAdd(
      Cube& cube,
      Sifteo::Side side,
      Cube& otherCube,
      Sifteo::Side otherSide) { return true; }

    virtual bool onNeighborRemove(
      Cube& cube,
      Sifteo::Side side,
      Cube& otherCube,
      Sifteo::Side otherSide) { return true; }
};

}
