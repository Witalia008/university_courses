def dct(dct,arr)
    s=0
    (0..7).each do |i|
         (0..7).each do |j|
             temp = 0.0
             (0..7).each do |x|
                 (0..7).each do |y|
                    temp = temp + $cos_t[i][x]*$cos_t[j][y]*arr[x][y][:blue]
                 end
             end
             dct[i][j] = $e[i][j]*temp
         end
    end
    return dct
end

def idct(dct,arr)
    (0..7).each do |i|
         (0..7).each do |j|
              temp = 0
              (0..7).each do |x|
                   (0..7).each do |y|
                        temp += dct[x][y]*$cos_t[x][i]*$cos_t[y][j]*$e[x][y]
                        arr[i][j][:blue] = (temp > 255) ? 255 : (temp < 0 ) ? 0 : temp.round;
                   end
              end
         end
    end
    return arr
end