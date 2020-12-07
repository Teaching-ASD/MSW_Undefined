#include"TextRenderer.h"

void TextRenderer::setOutputStream(const std::ostream &os){
    out.copyfmt(os);
}