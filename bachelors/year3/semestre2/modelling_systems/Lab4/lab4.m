function [] = lab4()
    original = im2double(imread('y2.bmp'));
    figure; 
    subplot(2, 2, 1); imshow(original);
    subplot(2, 2, 2); imshow(blur(original, 3));
    subplot(2, 2, 3); imshow(deblur_auto(blur(original, 3)));
    
    blurred = im2double(imread('y6.bmp'));
    [n, m] = size(blurred);
%     pad = 300;
%     blurred(n+1:n+pad,:) = zeros(pad, m);
%     blurred(:, m+1:m+pad) = zeros(n+pad, pad);
    figure;
    subplot(1, 2, 1); imshow(blurred);
    subplot(1, 2, 2); imshow(deblur_auto(blurred));
end

function [ blurred ] = blur(img, r)
    [n, m] = size(img);
    hf = fft2(fspecial('disk', r), n, m);
    blurred = real(ifft2(hf .* fft2(img)));
end

function [ focused ] = deblur(defocused, r, remove_noise)
    [n, m] = size(defocused);
    hf = fft2(fspecial('disk', r), n, m);
    if (remove_noise)
        focused = real(ifft2(fft2(defocused).*conj(hf)./(abs(hf).^2 + 1e-2)));
%         focused = real(ifft2((abs(hf) > 0.1).*fft2(defocused)./hf));
    else
        focused = real(fft2(defocused)./hf);
    end
end

function [ focused ] = deblur_auto(defocused)
    [n, m] = size(defocused);
    fres = 1e10;
    rres = -1;
    for r = 1:20
        temp = deblur(defocused, r, false);
        metric = var(temp(:));
        if metric < fres
            fres = metric;
            rres = r;
        end
    end
    rres
    focused = deblur(defocused, rres, true);
end