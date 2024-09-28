# Usage:
#
#   calc_log(<MESSAGE>)
#
# Notices a message with the CALC_LOG_PREFIX prefix.
#
function(calc_log MESSAGE)
    message(NOTICE "${CALC_LOG_PREFIX}: ${MESSAGE}")
endfunction()
