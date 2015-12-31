(gl:bind-buffer :array-buffer *vertex-buffer*)
(gl:vertex-attrib-pointer 0 3 :float nil 0 (cffi:null-pointer))
(gl:draw-arrays :triangles 0 3)
(gl:disable-vertex-attrib-array 0)